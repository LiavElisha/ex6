//
// Created by liav on 13/01/17.
//

#ifndef EX11_COMUNICATION_H
#define EX11_COMUNICATION_H

/* class name : Communication
 * Class that hold an array which by him the pthreds can communicate
 */
class Communication {

public:
    bool flag;
    int* array;
    int arraySize;
    int client;

    // constructor
    Communication();
    void InitializeTheArray(int n);
    void updtae(int x);
    void setFlag(bool b);
    void setCommond(int index, int commond);
    int getCommond(int index);

    void checkIfThredsDone();

    ~Communication();
};


#endif //EX11_COMUNICATION_H
