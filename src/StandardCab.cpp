//
// Created by yoav on 02/12/16.
//
#include <boost/serialization/export.hpp>
#include "StandardCab.h"
#include <deque>
using namespace std;
//constructor.
StandardCab::StandardCab(int cabId1,int meters1, char manufacturer1,
                         char color1,AbstractNode*& l){
 cabId=cabId1;
 type=1;
 meters=meters1;
 manufacturer = manufacturer1;
 color=color1;
 coefficient=1;
 location = l;
 speed=1;
 navigator=new Bfs();
    shortestPath = 0;
}

StandardCab::StandardCab() {
  cabId=0;
  type=1;
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


 void StandardCab::setSpeed(int speed1){
  speed =speed1;
 }
int StandardCab::getSpeed(){
 return speed;
}

float StandardCab::getTariff(){
 return coefficient;
}

int StandardCab::getType() {
 return type;
}
AbstractNode*& StandardCab::getLocation() {
 return location;
}

int StandardCab::getCabId() {
    return cabId;
}

int StandardCab:: moveOneStep(){
  location = shortestPath->front();
  shortestPath->pop_front();
    meters+=1;
 return 1;
}// the method that moves the cab.

void StandardCab::setShortestPath(deque<AbstractNode*>& path){
 shortestPath=&path;
}

deque<AbstractNode*> StandardCab::getShortestPath(){
    return *shortestPath;
}

Bfs*& StandardCab::getNavigator() {
 return navigator;
}


void StandardCab::addMetersPassed(int meters1) {
 meters+=meters1;
}
int StandardCab::getMeterPassed() {
 return meters;
}

void StandardCab::setLocation(AbstractNode*& location1) {
    location = location1;
}


StandardCab::~StandardCab() {
 delete(navigator);
};//destructor.

BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab");