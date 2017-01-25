//
// Created by yoav on 13/12/16.
//

#include <cstring>
#include <sstream>
#include "Menu.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
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
#include <mutex>
#include "Socket.h"
#include "Udp.h"
#include "Driver.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "TaxiCenter.h"
#include "Data.h"

pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER;
/*
 * Class name: Menu
 * the class is in charge of the entire input recieving and the entire flow of the program.
 */
Menu::Menu(TaxiCenter*& t,Socket* socket1) {
    taxiCenter =t;
    socket = socket1;
    socket->initialize();
    communication = new Communication();
}
/*
 * the method gets a string and an array of strings, and returns nothing.
 * the method parses the string into strings with the delimiter of "," and puts each
 * token in its place in the array.
 */
    void Menu::parseInput(string s,string* inputArr) {
    int i=0;
    istringstream iss(s);
    string token;
    while (getline(iss, token, ',')) {
        inputArr[i++] = token;
    }
}

/*
 * the method gets the amount of obstacles wanted and the x and y coordinate and initializes
 * them as obstacles on the matrix.
 */
void Menu::initializeObstacles(){
    int numberOfObstacles;
    cin>>numberOfObstacles;//gets the amount of obstacles.
    while (numberOfObstacles){//get each obstacle.
        int xObstacle, yObstacle;
        char dummy;
        cin>>xObstacle>>dummy>>yObstacle;
        NodePoint point(xObstacle,yObstacle);//get the proper node from the matrix.
        matrix->getNode((&point))->setIsObstacle();
        numberOfObstacles--;
    }
}
/*
 * the method initializes the matrix according to the size wanted and received by the console.
 */

void Menu::initializeMatrix() {
    int x,y;
    cin>>x>>y;// gets the size of the matrix.
    matrix = new Matrix(x,y);//create the proper matrix with the right measurments.
}

/*
 * the method gets a serializied driver through a socket and creates it in the server.
 * using deserialization and returns the drivers vehicle id.
 */

int Menu::receiveNewDriver() {
    Driver* driver;
    // desirialize the driver received from the client.
    char buffer[1024];
    memset(buffer,0,1024);
    socket->reciveData(buffer,sizeof(buffer), 0);  // receive the driver.
    boost::iostreams::basic_array_source<char> device(buffer,sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia>>driver;// deserialize the driver.
    taxiCenter->addDriver(driver);// set as a driver with the proper values.
    return driver->getVehicleId();
}


/*
 * the method gets a vehicle id of a certain driver and sends through a socket
 * to the client its cab only serialized.
 */
void Menu::sendProperTaxi(int cabId) {
    string serializedAbstractCab ;
    map<int, Driver *>::iterator it;//matches drivers and cabs.
    for (it = taxiCenter->getDriversMap().begin(); it !=
                                                   taxiCenter->
                                                           getDriversMap().end();
         it++) {// find the taxi of the driver.
        int cabid = it->second->getVehicleId();
        for (int i = 0; i < taxiCenter->getCabVector().size(); i++) {
            if (taxiCenter->getCabVector()[i]->getCabId() == cabid) {
                it->second->setCab(taxiCenter->getCabVector()[i]);
                // match the driver to the cab.
                boost::iostreams::back_insert_device<std::string> inserter
                        (serializedAbstractCab);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>>
                        s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << taxiCenter->getCabVector()[i];// serialize the taxi.
                s.flush();
                socket->sendData(serializedAbstractCab, 0);//send the taxi to the client.

            }
        }
    }
}


void Menu::getNewTrip(int id,int startX, int startY,int endX,int  endY, int numOfPassangers,
                      double tariff, int timeOfStart) {

    TripInformation *tripInformation = new TripInformation(id,
                                                           startX, startY,
                                                           endX, endY, numOfPassangers,
                                                           tariff, timeOfStart);

    // create the arguments of the function ComputeShortestWay
    Data* data = new Data(tripInformation, matrix, taxiCenter);
    // create thread that compute the shortest way
    pthread_t thread;
    pthread_create(&thread, NULL, ComputeShortestWay, (void*)data);

    //create a new trip.
    taxiCenter->addTrip(tripInformation);
    // add the trip to the taxicenter.
}


// static function for the thread that compute the shortest way and put it on the tripInformation
void* Menu::ComputeShortestWay(void* data1){
    Data* data = (Data*) data1;
    TripInformation *tripInformation = data->trip;
    Matrix* matrix = data->matrix;
    TaxiCenter* taxiCenter = data->taxiCenter;
    Bfs* b = taxiCenter->getNavigator();//get the navigator from the taxi center.
    AbstractNode* source = matrix->getNode(tripInformation->getSource());// get the source of the trip.
    AbstractNode* destination = matrix->getNode(tripInformation->getDestination()); // get the dest.

    pthread_mutex_lock(&locker);
    //finds a path from the drivers current location and where the passanger awaits.;
    deque<AbstractNode*>* deque1 = new deque<AbstractNode*> (b->theShortestWay(source,destination));
    pthread_mutex_unlock(&locker);


    if(!deque1->empty()){
        deque1->pop_front();
    }
    //get the path of the trip.
    tripInformation->setShortestPath(deque1);
    tripInformation->setComputeShortestWayDone();

    delete data;
}

void Menu::getNewCab(int id,int taxiType, int meters, char carMan,char color){
    NodePoint* n = new NodePoint(0,0);
    AbstractNode* n1 = matrix->getNode(n);
    delete n;

    if (taxiType == 1) {
        //create the new cab.
        StandardCab *standardCab = new StandardCab(id, 0, carMan, color,n1);
        taxiCenter->addCab((AbstractCab *&) standardCab);
        //add the cab to the taxicenter.
    } else if (taxiType == 2) {
        LuxuryCab *luxuryCab = new LuxuryCab(id, 0, carMan, color,n1);
        taxiCenter->addCab((AbstractCab *&) luxuryCab);
    }
}

/*
 * the method deletes all aloocated memory during the program.
 */
void Menu::shutDownProgram(){
    map<int, Driver *>::iterator it;//matches drivers and cabs.
    // socket->sendData("ShutDown", 0); // send the client a shut down command.
    for (it = taxiCenter->getDriversMap().begin(); it !=
                                                   taxiCenter->getDriversMap().end(); it++) {
        delete (it->second);    // delete all of the drivers.
    }
    delete (matrix);
    for(unsigned long i=0;i<taxiCenter->getCabVector().size();i++) {
        delete (taxiCenter->getCabVector()[i]);// delete the taxis.
        //check the erase.
    }
    for(unsigned long i=0;i<taxiCenter->getTripDeque().size();i++) {
        delete (taxiCenter->getTripDeque()[i]);//delete the trips.
    }
}

/*
 * signal the clients to drive.
 */
void Menu::signalClientToDrive(){
    socket->sendData("Drive", 0);// send the client a drive command.
}

/*
 * move all the drives in the server to maintain their location with accordance to the clients location.
 */
void Menu::moveDriversInServer(){
    int clientFlag =0;
    map<int, Driver *>::iterator it;
    for (it = taxiCenter->getDriversMap().begin(); it != taxiCenter->getDriversMap().end(); it++){
        it->second->moveOneStep(clientFlag, taxiCenter->getTime());//signal the drivers on the taxi center to move
        // to maintain their location with the client.
    }
}

/*
 * the method assigns trips to the drivers.
 */
void Menu::assignTrips(){

    map<int, Driver *>::iterator it;
    unsigned long numOfTrips = taxiCenter->getTripDeque().size();
    int taxiCenterTime =taxiCenter->getTime();
    Driver* driver = 0;
    for(unsigned long i=0;i < numOfTrips; i++) {// checks if there is a trip that needs to start.
        if (taxiCenter->getTripDeque()[i]->getStartTime() == taxiCenterTime) {
            // check which driver need get the trip
            for (it = taxiCenter->getDriversMap().begin(); it != taxiCenter->getDriversMap().end(); it++) {

                NodePoint *node1 = (NodePoint *) taxiCenter->getTripDeque()[i]->getSource();
                NodePoint *node2 = (NodePoint *) it->second->getCab()->getLocation();

                if (it->second->getAvailable() && *node1 == *node2) {
                    if (driver == 0) {
                        driver = it->second;
                    }
                    if (driver->getArriveToDestinationAt() > it->second->getArriveToDestinationAt()) {
                        driver = it->second;
                    }
                }
            }
            driver->setCurrentTrip(taxiCenter->getTripDeque()[i]);

            int id = driver->getDriverId();

            int index = threds.at(id);
            communication->array[index] = 1;
            communication->setFlag(false);
            while(!(communication->client)){}
            communication->checkIfThredsDone();
            communication->setFlag(true);
            int descriptorCommunicateClient = communication->client;
            communication->client = 0;
            // check that the pthred wich compute the shortest way done
            while (!taxiCenter->getTripDeque()[i]->getComputeShortestWayDone()){}

            int check1 = socket->sendData("AssignTrip", descriptorCommunicateClient);//send the client an assign trip command.
            while (check1 == 5){
                check1 = socket->sendData("AssignTrip", descriptorCommunicateClient);
            }
            string serializedTrip;
            boost::iostreams::back_insert_device<std::string> inserter(serializedTrip);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << taxiCenter->getTripDeque()[i];// serialize the trip.
            s.flush();
            int check2 = socket->sendData(serializedTrip, descriptorCommunicateClient);// send the client the serialized trip.
            while (check2 == 5){
                check2 = socket->sendData(serializedTrip, descriptorCommunicateClient);
            }
        }
    }
}


/*
 * the method is in charge of receiving the input from the user and create
 * the right objects accordingly
 * then it activates the moving method of each object according to the input.
 */
void Menu::getInput(){
    initializeMatrix();// initialize the matrix.
    initializeObstacles();// initialize the obstacles.
    int choice = 0;

    // {// the loop is active until the user hits the 7 key.
      do {
        cin>>choice;//gets the choice from the user.
        switch (choice) {
            case 1: {// add Driver.
                int amountOfDrivers;
                cin>>amountOfDrivers;
                int i = 0;
                // initialize the array of in communication for communicate betweem the threds
                communication->InitializeTheArray(amountOfDrivers);
                communication->flag = true;

                while (i<amountOfDrivers) {
                    int descriptorCommunicateClient = socket->openNewClient();
                    pthread_t thread;
                    Data* data = new Data(i, communication,descriptorCommunicateClient,socket,taxiCenter, &threds);
                    pthread_create(&thread, NULL, threadFunction, (void*)data);
                    i++;
                }
                communication->checkIfThredsDone();
                break;
                }

            case 2: {// add trip.
                string input;
                string inputArr[10];
                int id, startX, startY, endX, endY, numOfPassangers,timeOfStart;
                double tariff;
                cin >> input;
                parseInput(input, inputArr);
                id = atoi(inputArr[0].c_str());
                startX = atoi(inputArr[1].c_str());
                startY = atoi(inputArr[2].c_str());
                endX = atoi(inputArr[3].c_str());
                endY = atoi(inputArr[4].c_str());
                numOfPassangers = atoi(inputArr[5].c_str());
                tariff = atof(inputArr[6].c_str());
                timeOfStart =atoi(inputArr[7].c_str());
                getNewTrip( id, startX, startY, endX ,endY,  numOfPassangers, tariff, timeOfStart);
                break;
            }


            case 3: {// add Cab.
                string input;
                string inputArr[10];
                int id, taxiType;
                string carMan, color;
                cin >> input;
                parseInput(input, inputArr);
                id = atoi(inputArr[0].c_str());
                taxiType = atoi(inputArr[1].c_str());
                carMan = inputArr[2];
                color = inputArr[3];
                getNewCab(id,taxiType, 0, *carMan.c_str(), *color.c_str());
                break;
            }


            case 4: {// get the location of a certain driver.
                string input;
                string inputArr[10];
                int id;
                cin >> input;
                parseInput(input, inputArr);
                id = atoi(inputArr[0].c_str());
                NodePoint *location = (NodePoint *)taxiCenter->getDriverLocation(id);
                cout << *location ;
                break;
            }

            case 7: {// delete all the objects and quit from the program.
                communication->updtae(7);
                communication->setFlag(false);
                communication->checkIfThredsDone();
                shutDownProgram();
                break;
            }
            case 9: {   //signals the occupied drivers that it needs to move one step,+ moving the clock.

                communication->checkIfThredsDone();
                // say to the threds to send "drive" to the clients
                communication->updtae(9);
                communication->setFlag(false);
                taxiCenter->increaseClockBy1();
                communication->checkIfThredsDone();
                communication->setFlag(true);
                moveDriversInServer();
                assignTrips();
                break;
            }
            default: {
                cout << "wrong input"<<endl;
                break;
            }
        }

    }while(choice!=7);
}

// static function for the threadS that connect with the clients(drivers)
void* Menu::threadFunction(void* data1){
    Data* data = (Data*) data1;
    int index = data->index; // the index of the thred
    map<int, int>* threds = data->threds;
    Communication* communication = data->communication;
    int descriptorCommunicateClient = data->descriptorCommunicateClient;
    bool conditionStop = true;
    Socket* socket = data->socket;
    TaxiCenter* taxiCenter = data->taxiCenter;

    // get the driver from the user and put it on taxi center
    Driver* driver;
    // desirialize the driver received from the client.
    char buffer[1024];
    memset(buffer,0,1024);
    socket->reciveData(buffer,sizeof(buffer), descriptorCommunicateClient);  // receive the driver.
    // when the server get a message he sent to server ok

    // socket->sendData("ok",descriptorCommunicateClient);

    boost::iostreams::basic_array_source<char> device(buffer,sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia>>driver;// deserialize the driver.
    driver->setArriveToDestinationAt(index-communication->arraySize);
    taxiCenter->addDriver(driver);// set as a driver with the proper values.

    // map the driver id to his thred
    threds->insert ( std::pair<int,int>(driver->getDriverId(), index) );

    // send the cab to the client
    string serializedAbstractCab ;
    map<int, Driver *>::iterator it;//matches drivers and cabs.
    for (it = taxiCenter->getDriversMap().begin(); it !=
                                                   taxiCenter->
                                                           getDriversMap().end();
         it++) {// find the taxi of the driver.
        int cabid = it->second->getVehicleId();
        for (int i = 0; i < taxiCenter->getCabVector().size(); i++) {
            if (taxiCenter->getCabVector()[i]->getCabId() == cabid) {
                it->second->setCab(taxiCenter->getCabVector()[i]);
                // match the driver to the cab.
                boost::iostreams::back_insert_device<std::string> inserter
                        (serializedAbstractCab);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>>
                        s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << taxiCenter->getCabVector()[i];// serialize the taxi.
                s.flush();
                int check = socket->sendData(serializedAbstractCab, descriptorCommunicateClient);//send the taxi to the client.
                // check if the server get the driver, if not send again
                while (check==5){
                    check = socket->sendData(serializedAbstractCab, descriptorCommunicateClient);
                }
            }
        }
    }

    // inform the server that the client sent the driver and get his cab
    communication->setCommond(index, 0);

    int k = 0;
    while(conditionStop){
        while(communication->flag){}
        int choice = communication->getCommond(index);

        switch (choice){

            case 1:
                communication->client = descriptorCommunicateClient;
                communication->setCommond(index, 0);
                break;

            case 9:{
                int check = socket->sendData("Drive", descriptorCommunicateClient);
                while (check == 5){
                    check = socket->sendData("Drive", descriptorCommunicateClient);
                }
                communication->setCommond(index, 0);
                break;
            }
            case 7:{
                communication->setCommond(index, 0);
                int check = socket->sendData("ShutDown",descriptorCommunicateClient);
                while (check == 5){
                    check = socket->sendData("ShutDown", descriptorCommunicateClient);
                }
                conditionStop = false;
                break;
            }
            default:
                break;
        }
    }
    delete data;
}

Menu::~Menu() {
    delete communication;
};