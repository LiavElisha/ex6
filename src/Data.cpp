//
// Created by liav on 13/01/17.
//

#include "Data.h"

Data::Data(TripInformation* trip1, Matrix* matrix1, TaxiCenter* taxiCenter1){
    trip = trip1;
    matrix = matrix1;
    taxiCenter = taxiCenter1;

}

Data::Data(int index1, Communication* communication1, int descriptorCommunicateClient1, Socket* socket1, TaxiCenter* taxiCenter1, map<int,int>* threds1){
    index = index1;
    communication = communication1;
    descriptorCommunicateClient = descriptorCommunicateClient1;
    socket = socket1;
    taxiCenter = taxiCenter1;
    threds = threds1;

}

