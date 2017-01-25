//
// Created by liav on 01/12/16.
//

#include "Passanger.h"
Passanger::Passanger(NodePoint*& start, NodePoint*& end) {
    source=start;
    destination=end;

}
int Passanger::satisfactionFromRide(){
    return rand()%6;
}

Passanger::~Passanger() {};
