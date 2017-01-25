//
// Created by liav on 13/01/17.
//

#ifndef EX11_DATA_H
#define EX11_DATA_H


#include "TripInformation.h"
#include "Matrix.h"
#include "TaxiCenter.h"
#include "Communication.h"
#include "Socket.h"
/* class name : Data
 * Class that transfer arguments for pthreds function
 */
class Data {

public:
    Data(TripInformation* trip1, Matrix* matrix1, TaxiCenter* taxiCenter1);
    Data(int index1, Communication* communication1, int descriptorCommunicateClient1, Socket* socket1, TaxiCenter* taxiCenter1, map<int,int>* threds1);

    TripInformation* trip;
    Matrix* matrix;
    pthread_mutex_t* matrix_locker;
    TaxiCenter* taxiCenter;

    Socket* socket;
    int descriptorCommunicateClient;
    int index;
    Communication* communication;
    map<int,int>* threds;
};


#endif //EX11_DATA_H
