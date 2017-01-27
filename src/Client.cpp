#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include "Socket.h"
#include "Driver.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "TaxiCenter.h"
#include "Tcp.h"
#include "InputValidator.h"
#include <vector>

using namespace std;
using namespace boost::archive;

int main(int argc, char *argv[]){
    InputValidator inputValidator;
    int portNumber = atoi(argv[2]); // getting the port number from the arguments of the main.
    Socket* socket = new Tcp(0,portNumber);//creating a new socket -tcp.
    vector <string>* driverInput = inputValidator.validateInputForNewDriver();
     if(driverInput == 0){
         delete(socket);
         return 0;
     }

    socket->initialize();   //initialize the socket.
    char buffer[130000];  // define a buffer for the serialization.
    memset(buffer,0,130000);
    AbstractCab* mycab;
    int id,age,experience,vehicleId;// recieving a driver.
    string status;

    id = atoi((*driverInput)[0].c_str());
    age = atoi((*driverInput)[1].c_str());
    status = (*driverInput)[2];
    experience =atoi((*driverInput)[3].c_str());
    vehicleId = atoi((*driverInput)[4].c_str());
    Driver* driver = new Driver(id,age,*status.c_str(),vehicleId,experience);    //receive new driver.


    //serialized the driver.
    string serializedDriver ;
    boost::iostreams::back_insert_device<std::string> inserter(serializedDriver);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();


    //send the serialized driver to the server.
    int check = socket->sendData(serializedDriver, 0);
    // check if the server get the driver, if not send again
    while (check==5){
        check = socket->sendData(serializedDriver, 0);
    }

    //received the matching taxi from the server for the driver sent before.
    socket->reciveData(buffer,sizeof(buffer), 0);
    // when the client get the cab, he sent ok

    boost::iostreams::basic_array_source<char> device(buffer,sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia>>mycab;//deserialize the taxi received.
    driver->setCab(mycab);// setting the taxi as the drivers cab.

    
    int endFlag = 0;
    int clientFlag =1;

    int k = 0;
    int j = 1;
    while(endFlag!=1){
        memset(buffer,0,130000);
        socket->reciveData(buffer,sizeof(buffer), 0);//wait for a command.

        if(strcmp(buffer,"AssignTrip") == 0) {
            TripInformation* tripInformation;
            memset(buffer,0,130000);
            socket->reciveData(buffer,sizeof(buffer), 0);// receive the trip.
            boost::iostreams::basic_array_source<char> device(buffer,sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            boost::archive::binary_iarchive ia(s2);
            ia>>tripInformation;// deserialize the trip.
            driver->setCurrentTrip(tripInformation);// set as the current trip.
        }

        if(strcmp(buffer,"Drive") == 0){
            driver->moveOneStep(clientFlag, -1);
        }

        if(strcmp(buffer,"ShutDown") == 0){
            TripInformation* trip = driver->getCurrentTrip();
            if (trip !=0){
                while (trip->getRouteLength()!=0){
                    delete (trip->getNextPointOnRounte());
                }
                delete(trip);
            }
            delete (driver->getCab()->getLocation());
            delete (driver);
            delete (mycab);
            endFlag=1;
        }
    }
    // close the socket
    delete socket;
}
