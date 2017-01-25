//
// Created by liav on 01/12/16.
//

#ifndef EX11_DRIVER_H
#define EX11_DRIVER_H

#include <iostream>
#include "AbstractCab.h"
#include "TripInformation.h"
#include "Bfs.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
#include <boost/serialization/deque.hpp>
using namespace std;
using namespace boost::archive;
/* class name : Driver
 * Class that create new drivers
 */
class Driver {

private:
    //members.
    int driverId;
    int vehicleId;
    int age;
     char status;
    int yearsOfExperience;
    float avarageSatisfaction;
    bool available;
    AbstractCab* myCab;
    TripInformation* currentTrip;
    int arriveToDestinationAt;

public:
    // constructors
    Driver(int driverId2, int age2, char maritalStatus);
    Driver(int driverId1, int age1, char maritalStatus,int vid);
    Driver(int driverId1, int age1, char maritalStatus,int vid, int yearsOfExp);
    Driver();
    friend class boost::serialization::access;
    template<class Archive>


    void serialize(Archive &ar, const unsigned int version)
    {
        ar & driverId;
        ar & vehicleId;
        ar & age;
        ar & status;
        ar & yearsOfExperience;
        ar & avarageSatisfaction;
        ar & available;
        //ar & myCab;
        //ar & currentTrip;
    }


    // get and set functions
    void setAvailable(bool avail);
    bool getAvailable();

    void setAge(int age2);
    int getAge();

    void setMaritalStatus(char maritalStatus);
    int getMaritalStatus();

    void setYearsOfExperience(int years);
    int getYearsOfExperience();

    int getDriverId();
    int getVehicleId();
    void setVehicleId(int id);

    void setCab(AbstractCab*& abstractCab);
    AbstractCab*& getCab();

    void setCurrentTrip(TripInformation*& trip);
    TripInformation* getCurrentTrip();
    int getArriveToDestinationAt();
    void setArriveToDestinationAt(int time);

    void startDriving(Matrix*& matrix);
    // the method notifies the cab to move one step until it gets to the destination.
    void moveOneStep(int clientFlag, int time);






    // destructor
    ~ Driver();

};


#endif //EX11_DRIVER_H