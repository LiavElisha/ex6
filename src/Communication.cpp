//
// Created by liav on 13/01/17.
//

#include "Communication.h"


// constructor
Communication::Communication(){
    arraySize = 0;
    flag = true;
    client = 0;
}
void Communication:: InitializeTheArray(int n){
    array = new int[n];
    client = 0;
    for(int i = 0; i<n; i++){
        array[i] = 1;
    }
    arraySize = n;

}
// update the array at an specific value
void Communication::updtae(int x) {
    for(int i = 0; i < arraySize; i++){
        array[i] = x;
    }
}

void Communication::setFlag(bool b){
    flag = b;
}
void Communication::setCommond(int index, int commond){
    array[index] = commond;
}

int Communication::getCommond(int index){
    return array[index];
}

// if all the values in the arrays are 0, return
void Communication::checkIfThredsDone(){
    for (int j = 0; j < arraySize; j++){
        while(1){
            if (array[j] == 0){
                break;
            }
        };
    }
}



Communication::~Communication(){
    delete [] array;
}
