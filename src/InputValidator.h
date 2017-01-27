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


class InputValidator {
private:
    vector<int> matrixInput;
    vector<string> intermediateInputVec;
    vector<int> intermediateIntInput;
    vector <string> tripInformationInput;


public:
    int checkIfIsAvalidNumber(string input,int min, int max);
    void parseInputByDelimiter(string input, char delimiter);
    void emptyIntermediateVec();
    void emptyTheTripVec();
    InputValidator();
    void validateDimenstionOfMatrix();
    int validateInputForObstacles();
    vector <int>*  validateInputForMatrix();
    void emptyTheMatrixVec();
    vector <string>*  validateInputForTripInformation(int xDim, int yDim);
    int checkIfThereAreSpaces(string input);


};


#endif //EX6_INPUTVALIDATOR_H
