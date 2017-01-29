//
// Created by liav on 01/12/16.
//
#include <deque>
#include "Driver.h"

Driver::Driver(int driverId2, int age2, char maritalStatus){
    driverId = driverId2;
    age = age2;
    available = true;
    yearsOfExperience = 0;
    status=maritalStatus;
    vehicleId =0;
    avarageSatisfaction=0;
    myCab=0;
    currentTrip=0;
    arriveToDestinationAt=0;
}
//construcor.
Driver::Driver(int driverId1, int age1, char maritalStatus, int vid){
    driverId = driverId1;
    age = age1;
    available = true;
    yearsOfExperience = 0;
    status=maritalStatus;
    vehicleId =vid;
    avarageSatisfaction=0;
    myCab=0;
    currentTrip=0;
    arriveToDestinationAt=0;
}
//construcor.
Driver::Driver(int driverId1, int age1, char maritalStatus,int vid, int yearsOfExp) {
    driverId=driverId1;
    age=age1;
    status=maritalStatus;
    vehicleId=vid;
    yearsOfExperience=yearsOfExp;
    available= true;
    avarageSatisfaction=0;
    myCab=0;
    currentTrip=0;
    arriveToDestinationAt=0;
}
//construcor.
Driver::Driver(){
    driverId=0;
    age=0;
    status=0;
    vehicleId=0;
    yearsOfExperience=0;
    available= true;
    avarageSatisfaction=0;
    myCab=0;
    currentTrip=0;
    arriveToDestinationAt=0;
}
//construcor.
void Driver::setAvailable(bool avail){
//sets the driver as available for future trips..
    available=avail;
}

bool Driver::getAvailable(){
//returns whether the driver is available for a trip or not.
    return available;
}

void Driver::setAge(int age2){
    age=age2;
}
int Driver::getAge(){
    return age;
}

void Driver::setMaritalStatus(char matrialStatus) {
    status=matrialStatus;
}
int Driver::getMaritalStatus(){
    return status;
}

void Driver::setYearsOfExperience(int years){
    yearsOfExperience=years;
}
int Driver::getYearsOfExperience(){
    return yearsOfExperience;
}

int Driver::getDriverId(){
    return driverId;
}
int Driver::getVehicleId(){
    return vehicleId;
}

void Driver::setVehicleId(int id){
    vehicleId=id;
}

void Driver::setCab(AbstractCab *&abstractCab) {
//sets the drivers cab member as the member it got as a reference/
        myCab=abstractCab;
}

AbstractCab*& Driver::getCab(){
 return myCab;
}

void Driver::setCurrentTrip(TripInformation *&trip) {
    currentTrip=trip;
}

TripInformation* Driver::getCurrentTrip(){
    return currentTrip;
}
int Driver::getArriveToDestinationAt(){
    return arriveToDestinationAt;
}
void Driver::setArriveToDestinationAt(int time){
    arriveToDestinationAt = time;
}



void Driver::moveOneStep(int clientFlag, int time){
    if(currentTrip == 0){
        return;
    }
    if(currentTrip->getRouteLength() == 0){
        return;
    }
    if(myCab ->getType() == 2){ // is a luxuryCab
        if(currentTrip->getRouteLength()>= 2){
            if(clientFlag) {
                
                delete (myCab->getLocation());

                
            }
            myCab->setLocation(currentTrip->getNextPointOnRounte());
            if(clientFlag) {
                
                delete (myCab->getLocation());

            }
            myCab->setLocation(currentTrip->getNextPointOnRounte());
            myCab->addMetersPassed(2);
            if(*(NodePoint*)currentTrip->getDestination() == *(NodePoint*) myCab->getLocation()){
                if(clientFlag) {
                    delete (currentTrip);
                    currentTrip =0;
                }
                available = true; //the driver is now available for the next trip.
                if (time > 0){
                    arriveToDestinationAt = time;
                }
            }
        }else {// the trip is in the length of 1.
            if(clientFlag) {
                delete (myCab->getLocation());
            }
            myCab->setLocation(currentTrip->getNextPointOnRounte());
            myCab->addMetersPassed(1);
            if(clientFlag) {
                delete (currentTrip);
                currentTrip =0;
            }
            currentTrip=0;
            available = true; //the driver is now available for the next trip.
            if (time > 0){
                arriveToDestinationAt = time;
            }
            //do something we ended the trip.
        }
    }else {// StandardCab.
        if(clientFlag) {
            delete (myCab->getLocation());


        }
        myCab->setLocation(currentTrip->getNextPointOnRounte());
        myCab->addMetersPassed(1);
        if(*(NodePoint*)currentTrip->getDestination() == *(NodePoint*) myCab->getLocation()){
            if(clientFlag) {
                delete (currentTrip);
                currentTrip =0;
            }
            available = true; //the driver is now available for the next trip.
            if (time > 0){
                arriveToDestinationAt = time;
            }
        }
    }


}

Driver::~ Driver(){}