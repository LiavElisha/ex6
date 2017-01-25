//
// Created by yoav on 02/12/16.
//
#include "AbstractCab.h"
#include "LuxuryCab.h"
#include <boost/serialization/export.hpp>

//constructor.
LuxuryCab::LuxuryCab(int cabId1 ,int meters1, char manufacturer1,
                     char color1, AbstractNode*& l){
    cabId=cabId1;
    type=2;
    meters=meters1;
    manufacturer = manufacturer1;
    color=color1;
    coefficient=1;
    location = l;
    speed=1;
    navigator=new Bfs();
    shortestPath = 0;
}

LuxuryCab::LuxuryCab() {
    cabId=0;
    type=2;
    meters=0;
    manufacturer = 0;
    color=0;
    coefficient=1;
    speed=0;
    navigator=new Bfs();
    location=0;
    shortestPath = 0;
}

//getters and setters.
void LuxuryCab::setSpeed(int speed1){
    speed=speed1;
}
int LuxuryCab::getSpeed(){
    return speed;
}
float LuxuryCab::getTariff(){
    return coefficient;
}

//may need it to next missions.
int LuxuryCab:: moveOneStep(){
    if(shortestPath->size()>=2){
        shortestPath->pop_front();
        location=shortestPath->front();
        shortestPath->pop_front();
        meters+=2;
        return 2;
    } else {
        location=shortestPath->front();
        shortestPath->pop_front();
        meters+=1;
        return 1;
    }
}

int LuxuryCab::getType() {
    return 2;
}
AbstractNode*& LuxuryCab::getLocation() {
    return location;
}
int LuxuryCab::getCabId() {
    return cabId;
}

 void LuxuryCab::setShortestPath(deque<AbstractNode*>& path){
    shortestPath= &path;
}

deque<AbstractNode*> LuxuryCab::getShortestPath(){
    return *shortestPath;
}

Bfs*& LuxuryCab::getNavigator() {
    return navigator;
}

void LuxuryCab::addMetersPassed(int meters1) {
    meters+=meters1;
}

int LuxuryCab::getMeterPassed() {
    return meters;
}

void LuxuryCab::setLocation(AbstractNode*& location1) {
    location = location1;
}



LuxuryCab::~LuxuryCab(){
    delete(navigator);
};//destructor.

BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab");