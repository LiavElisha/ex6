//
// Created by yoav on 26/01/17.
//

#ifndef EX6_INPUTVALIDATOR_H
#define EX6_INPUTVALIDATOR_H

#include <vector>
#include "iostream"
#include <cstring>
#include <sstream>
using namespace std;
#define matrixDimensionsSize  2;


class InputValidator {
private:
    vector<int> matrixInput;
    int matrixDimensions [2];
    vector<string> obstaclesVec;
    vector<string> intermediateInputVec;
    vector<int> intermediateIntInput;


public:
    int checkIfIsAvalidNumber(string input,int min, int max);
    void parseInputByDelimiter(string input, char delimiter);
    void emptyIntermediateVec();
    InputValidator();
    int getAPositiveNumber();
    void validateDimenstionOfMatrix();
    int validateInputForObstacles();
    vector <int>*  validateInputForMatrix();
    void emptyTheMatrixVec();


};


#endif //EX6_INPUTVALIDATOR_H
