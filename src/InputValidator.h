//
// Created by yoav on 26/01/17.
//

#ifndef EX6_INPUTVALIDATOR_H
#define EX6_INPUTVALIDATOR_H

#include <vector>
#include "iostream"
#include "Driver.h"
#include <cstring>
#include <sstream>
#include <map>

using namespace std;


class InputValidator {
private:
    vector<int> matrixInput;
    vector<string> intermediateInputVec;
    vector<int> intermediateIntInput;
    vector <string> tripInformationInput;
    vector<string> taxiInputVec;
    vector<string>driverInputVec;
    vector<string>doubleVec;
public:
    double checkIfIsAvalidDouble(string input, double min, double max);
    int checkIfIsAvalidNumber(string input,int min, int max);
    void parseInputByDelimiter(string input, char delimiter);
    void emptyIntermediateVec();
    void emptyTheTripVec();
    void emptyTaxiInputVec();
    InputValidator();
    void validateDimenstionOfMatrix();
    int validateInputForObstacles();
    vector <int>*  validateInputForMatrix();
    void emptyTheMatrixVec();
    int checkIfThereAreSpaces(string input);
    vector <string>*  validateInputForTripInformation(int xDim, int yDim);
    vector <string>*  validateInputForTaxi();
    int validateInputForDriversLocation(map<int,Driver*> driversMap);
    vector <string>*  validateInputForNewDriver();
    int validateAmountOfDrivers();
};


#endif //EX6_INPUTVALIDATOR_H
