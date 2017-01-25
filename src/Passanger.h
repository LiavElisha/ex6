//
// Created by liav on 01/12/16.
//

#ifndef EX11_PASSANGER_H
#define EX11_PASSANGER_H

#include <stdlib.h>
#include "NodePoint.h"
/*
 * lass name: Passanger.
 *
 */
class Passanger {


private:
    NodePoint* source;
    NodePoint* destination;

public:
    Passanger(NodePoint*& start, NodePoint*& end);//constructor.
    int satisfactionFromRide();//the method returns a random number on the range of 1-5.
    ~Passanger();//destructor.
};


#endif //EX11_PASSANGER_H
