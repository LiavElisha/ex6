//
// Created by liav on 01/12/16.
//

#include "TripInformation.h"
#include "Bfs.h"

TripInformation::TripInformation(){ //for debugging
    rideId = 0;
    source = 0;
    destination =0;
    tariff = 0;
    numberOfPassangers=0;
    timeOfStart=0;
    meterPassed = 0;
    computeShortestWayDone = false;
     done = false;
}

TripInformation::TripInformation(int rideId2, int meterPassed2, AbstractNode* source2,
                                 AbstractNode* destination2 , double tariff2, int pass){
    rideId = rideId2;
    meterPassed = 0;
    source = source2;
    destination = destination2;
    tariff = tariff2;
    numberOfPassangers=pass;
    computeShortestWayDone = false;
     done = false;

}
TripInformation::TripInformation(int rideId2, int xStart, int yStart, int xEnd, int yEnd,
                                  int pass, double tariff2, int timeOfStart1){
    rideId = rideId2;
    source = new NodePoint(xStart,yStart);
    destination = new NodePoint(xEnd,yEnd);
    tariff = tariff2;
    numberOfPassangers=pass;
    timeOfStart=timeOfStart1;
    meterPassed = 0;
    computeShortestWayDone = false;
     done = false;
}



void TripInformation::setMetersPassed(int meters){
    meterPassed=meters;
}
int TripInformation::getMetersPassed(){
    return meterPassed;
}

AbstractNode*& TripInformation::getSource(){
    return  source;
}

AbstractNode*& TripInformation::getDestination(){
    return  destination;
}

void TripInformation::setTariff(double tariff1){
    tariff= tariff1;
}

double TripInformation::getTariff(){
    return tariff;
}
int TripInformation:: getRideId(){
    return rideId;
};

AbstractNode*& TripInformation::getNextPointOnRounte(){
    if(!shortestPath->empty()) {
        AbstractNode *&p1 = shortestPath->front();
        shortestPath->pop_front();
        return p1;
    }
}

void TripInformation::setShortestPath(deque<AbstractNode*>*& path){
    shortestPath= path;
    if (shortestPath->size() == 0){
        this->timeOfStart = -1;
    }
    length = this->getRouteLength();
    done = true;
}

unsigned long TripInformation::getRouteLength(){
    if(shortestPath!= 0) {
        return shortestPath->size();
    }
    return 0;
}

int TripInformation::getStartTime(){
    return timeOfStart;
}
void TripInformation::setStartTime(int s){
    timeOfStart=s;
}

void TripInformation::setComputeShortestWayDone(){
    computeShortestWayDone = true;
}
bool TripInformation::getComputeShortestWayDone(){
    return computeShortestWayDone;
}


 TripInformation::~TripInformation() {
     delete(shortestPath);
     delete(source);
     delete(destination);
 }

