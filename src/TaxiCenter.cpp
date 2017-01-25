//
// Created by yoav on 02/12/16.
//

#include "TaxiCenter.h"
#include <map>
/*
 * class name: TaxiCenter.
 * the class that holds all of the cabs, trips and drivers.
 */
TaxiCenter::TaxiCenter(){
    clock = 0;
    navigator = new Bfs();
};//constructor.
void TaxiCenter::answerCalls(){};//a method that answer calls and adds a trip accordingly.

void TaxiCenter::addDriver(Driver*& driver){ //a method that adds a driver.
   driversMap[driver->getDriverId()]= driver;
}

void TaxiCenter::addTrip(TripInformation*& tripInformation){ // a method that adds a trip.
    tripDeque.push_back(tripInformation);
}
void TaxiCenter::addCab(AbstractCab*& abstractCab){
    cabVector.push_back(abstractCab);
}// a method that adds a cab.

map<int,Driver*>& TaxiCenter::getDriversMap(){
    return driversMap;

}// a method that returns the map of drivers.


vector<TripInformation*>& TaxiCenter::getTripDeque(){
    return tripDeque;
}// a method that returns the trip deque.



vector<AbstractCab*>& TaxiCenter::getCabVector(){
    return cabVector;

}// a method that returns a list of cabs.
AbstractNode* TaxiCenter::getDriverLocation(int id) {
    int cabId = driversMap[id]->getVehicleId();
    for (int i = 0; i < cabVector.size(); i++) {
        if (cabVector[i]->getCabId() == cabId) {
            return cabVector[i]->getLocation();
        }
    }
    return 0;
}

int TaxiCenter::getTime(){
    return clock;
}

void TaxiCenter::increaseClockBy1(){
    clock+=1;
}



Bfs*& TaxiCenter::getNavigator() {
    return navigator;
}

TaxiCenter::~TaxiCenter() {
    delete (navigator);
};


