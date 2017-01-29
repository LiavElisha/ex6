//
// Created by yoav on 26/01/17.
//

#include <limits>
#include "InputValidator.h"
#include "Driver.h"
#include <map>

using namespace std;

InputValidator::InputValidator(){

}


/*
 * the method gets a string and a delimiter ands splits it into token where each token is pushed to a vector
 * of strings.
 */
void InputValidator::parseInputByDelimiter(string input, char delimiter){
    string token;
    istringstream iss(input);///cast to istring stream.
    while (getline(iss, token, delimiter)) {
        intermediateInputVec.push_back(token);///split it into tokens.
    }
}

/*
 * the method gets a string and a range which the string should be between.
 * first it checks if all of its components are digits and then it checks if the number is in the range given if
 * one is given.
 * if it isn't it returns -1 otherwise it returns the num.
 *
 */
double InputValidator::checkIfIsAvalidDouble(string input, double min, double max){
    int thereIsAMaximumValFlag =0;
    int thereIsAMinimumValFlag =0;
    if(min != -1){
        thereIsAMinimumValFlag = 1;
    }
    if(max != -1){
        thereIsAMaximumValFlag=1;
    }


    string token;
    istringstream iss(input);
    while (getline(iss, token, '.')) {///split into tokens by spaces.
        doubleVec.push_back(token);///push to an input vector.
    }

if(doubleVec.size() >2){///we have more than 2 parameters.
    emptyIntermediateVec();///the input is incorrect so we make the vector empty.
        return -1;
    }
    int num = checkIfIsAvalidNumber(doubleVec[0],-1,-1);///check that each of the parts is a valid number.
    if(doubleVec.size()>1) {
        int frac = checkIfIsAvalidNumber(doubleVec[1], -1, -1);
        if(frac== -1 ){
            emptyIntermediateVec();
            return -1;
        }
    }
    if(num  ==  -1){
        emptyIntermediateVec();
        return -1;
    }///if it isn't than the input is invalid.
    double tempNum = atof(input.c_str());///cast the string into a double.
    if(thereIsAMinimumValFlag) {/// check if we have a minimum value to consider.
        if (tempNum <= min) {///if there is and the value is smaller than the input is invalid.
            emptyIntermediateVec();
            return -1;
        }
    }
    if(thereIsAMaximumValFlag) {///check if there is a maximum value to take in considiration.
        if (tempNum > max) {
            emptyIntermediateVec();
            return -1;///if there is and the value is bigger thean the maximum then the input is invalid.
        }
    }
    while(!doubleVec.empty()){///else empty the input vector.
        doubleVec.pop_back();
    }
    return tempNum;///return the value casted into double.
}


/*
 * the method gets a string and a range which the string should be between.
 * first it checks if all of its components are digits and then it checks if the number is in the range given if
 * one is given.
 * if it isn't it returns -1 otherwise it returns the num.
 *
 */
int InputValidator::checkIfIsAvalidNumber(string input,int min, int max){

    int thereIsAMaximumValFlag =0;
    int thereIsAMinimumValFlag =0;
    if(min != -1){///check if there is a minimum value we need to take in considiration.
        thereIsAMinimumValFlag = 1;
    }
    if(max != -1){///check if there is a maximum value we need to take in considiration.
        thereIsAMaximumValFlag=1;
    }


    unsigned long length = input.size();///check the length of the string.
    int tempNum= 0;
    for (int i=0;i<length;i++){///go through all the elements of the string char by char.
        ///and if the current char is a digit take it, multiply the number by 10 and add the element.
        if(isdigit(input[i])){
            tempNum = 10*tempNum+(input[i]-'0');
        } else{
            return -1;///else return invalid input.
        }
    }
    if(thereIsAMinimumValFlag){///check if we need to take in considiration a minimum value.
        if (tempNum < min) {
            return -1;
        }
    }
    if(thereIsAMaximumValFlag){///check if we need to take in considiration a maximum value.
        if (tempNum > max) {
            return -1;
        }
    }
    return tempNum;
}



/*
 * the method empties the vectors of string in case that the input was incorrect
 * and new input should be insrted.
 */
void InputValidator::emptyIntermediateVec(){
    while(!intermediateInputVec.empty()){
        intermediateInputVec.pop_back();
    }
    while(!intermediateIntInput.empty()){
        intermediateIntInput.pop_back();
    }
    while(!doubleVec.empty()){
        doubleVec.pop_back();
    }
}

/*
 * the method other method for splitting the input into tokens then it checks if each
 * parameter given is a number and then if it is then it inserts them into a vector of strings.
 * otherwise it receives a new input until it is correct.
 */
void InputValidator::validateDimenstionOfMatrix(){
    int isValid = 0;
    string dimensions;
    int validNum;
    while(isValid!=1) {///run until we get a correct input.
        std::cin.clear(); // clears error flags
        std::getline(std::cin, dimensions);
        boost::algorithm::trim(dimensions);///trim the string from white spaces.
        parseInputByDelimiter(dimensions, ' ');///split into tokens by spaces.
        if(intermediateInputVec.size() == 2) {///check if the size is 2 or not.
            for (int i = 0; i < 2; i++) {
                validNum = checkIfIsAvalidNumber(intermediateInputVec[i], 1, 1000);
                ///the maximum valiue is 1000 and the minimum is 1.
                if (validNum == -1) {///if we got an unvalid input then start over.
                    emptyIntermediateVec();
                    std::cout << "-1" << endl;
                    break;
                } else {///else push the proper elements to the correct vector.
                    intermediateIntInput.push_back(validNum);
                }
            }
            if (intermediateIntInput.size() == 2) {///double check that the input was fine.
                isValid = 1;
            }
        }else {
            emptyIntermediateVec();
            std::cout << "-1" << endl;
        }

    }
    matrixInput.push_back(intermediateIntInput[0]);
    matrixInput.push_back(intermediateIntInput[1]);
    emptyIntermediateVec();///empty all of the intermediate vectors used for computation.
}


/*
 *  the method gets a string and parses it by the delimiter "space" =' ' and pushes it into a vector,
 *  if it has spaces that means that there are more than one element in the vector then it returns -1.
 *  else it returns 0.
 */

int InputValidator::checkIfThereAreSpaces(string input){
    parseInputByDelimiter(input,' ');
    if(intermediateInputVec.size()!=1) {
        return -1;
    }
    else return 0;
}



/*
 * the method verifies the the input was given as obstacles is valid it returns -1 if it isn't and 0 otherwise.
 * first it uses other methods to split the input into tokens by comma, then it checks if each component
 * is a number and if so that it is in the range of the matrix. if so it pushes the input into the input
 * vector.
 */
int InputValidator::validateInputForObstacles() {
        string obstacle;
        string  numberOfObstacles;
        int amountOfObstacles;
        std::cin.clear(); // clears error flags
        std::getline(std::cin, numberOfObstacles);///get the input
        boost::algorithm::trim(numberOfObstacles);///trim the input.
        int thereAreSpaces = checkIfThereAreSpaces(numberOfObstacles);///check if there is an extra space.
        if(thereAreSpaces == -1){
                std::cout << "-1" << endl;
                return -1;
        }
    ///check if it is a valid amount.
        amountOfObstacles = checkIfIsAvalidNumber(numberOfObstacles,0,-1);
        if(amountOfObstacles == -1) {
            std::cout << "-1" << endl;
            return -1;
        }
    emptyIntermediateVec();
    std::cin.clear(); // clears error flags
    matrixInput.push_back(amountOfObstacles);///push the input which was valid so far.
    for (int i = 0; i < amountOfObstacles; i++) {///run as many times as the amount of obstacles.
        std::getline(std::cin, obstacle);///get the obstacle.
        boost::algorithm::trim(obstacle);///trim if from spaces.
        parseInputByDelimiter(obstacle,' ');///split it by spaces.
        if (intermediateInputVec.size() != 1) {///if there was an extra spaces the input is invalid.
            std::cout << "-1" << endl;
            return -1;
        } else {
            obstacle = intermediateInputVec.front();
            emptyIntermediateVec();
            parseInputByDelimiter(obstacle,',');///else split it by comma.
            if (intermediateInputVec.size() != 2) {
                ///if the size of the vector is more than 2 then the input is invalid
                std::cout << "-1" << endl;
                return -1;
            } else {
                ///check that each component is valid
                int xVal = checkIfIsAvalidNumber(intermediateInputVec[0],0,matrixInput[1]-1);
                int yVal = checkIfIsAvalidNumber(intermediateInputVec[1],0,matrixInput[0]-1);
                if ((xVal == -1 || yVal == -1)|| (xVal ==0 && yVal == 0)) {
                    std::cout << "-1" << endl;
                    return -1;
                }else {
                    matrixInput.push_back(xVal);///push it to the vecor.
                    matrixInput.push_back(yVal);
                    emptyIntermediateVec();
                }
            }
        }
    }
    return 0;

}
/*
 * the method empties the vector of the matrix input .
 */
void InputValidator::emptyTheMatrixVec() {
    while(!matrixInput.empty()){
        matrixInput.pop_back();
    }
}


/*
 * the method empties the vector.
 */
void InputValidator::emptyTheTripVec() {
    while(!tripInformationInput.empty()){
        tripInformationInput.pop_back();
    }
}

void InputValidator::emptyTaxiInputVec() {
    while(!taxiInputVec.empty()){
        taxiInputVec.pop_back();
    }
}




/*
 * the method verifies that the input given as matrix is valid, first it checks if the matrix dimension
 * are correct or not and then if the obstacles give.
 * if not it keeps getting input until it receives a valid input and if it is correct it returns
 * a vector of ints where the first parameter is the x dimension of the matrix, the second is the y dimension
 * the third is the number of obstacles and then each pair is an obstacle.
 */
vector<int>*  InputValidator::validateInputForMatrix(){
    int validateObs=0;
    int isValid=0;
    while(!isValid) {
        validateDimenstionOfMatrix();
        validateObs = validateInputForObstacles();
        if(validateObs == -1){
            emptyIntermediateVec();
            emptyTheMatrixVec();
        }else {
            return &matrixInput;
        }
    }
}

vector <string>*  InputValidator::validateInputForTripInformation(int xDim, int yDim) {
    if (!intermediateInputVec.empty()) {
        emptyIntermediateVec();
        emptyTheTripVec();
    }
    string input;
    int min;
    int max;
    std::cin.clear(); // clears error flags
    std::getline(std::cin, input);
    boost::algorithm::trim(input);
    int therAreSpaces = checkIfThereAreSpaces(input);
    if (therAreSpaces == -1) {
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    emptyIntermediateVec();
    parseInputByDelimiter(input, ',');
    if (intermediateInputVec.size() != 8) {
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if (i > 0 && i < 5) {/// the points should be in the range of the matrix( 1<=i<=4).
            if (i % 2 == 0) {/// thx value shoud be in the range of the matrix.
                min = 0;
                max = xDim - 1;
            } else {///the y value should be in the range of the matrix.
                min = 0;
                max = yDim - 1;
            }
        } else if (i == 0) {/// the id should be bigger then 0.
            min = 0;
            max = -1;
        } else {/// the passanger amount and the time should be bigger than 1.
            min = 1;
            max = -1;
        }
        if (i == 6) {///the tariff should be bigger then 0.
            min = 0;
            max = -1;
            double num = checkIfIsAvalidDouble(intermediateInputVec[i], min, max);
            ///check that the tariff is a valid double and that it is in the proper range
            if (num == -1) {
                emptyIntermediateVec();
                std::cout << "-1" << endl;
                return 0;
            }
        } else {///check that all of the numbers are in the proper range.
            int num = checkIfIsAvalidNumber(intermediateInputVec[i], min, max);
            if (num == -1) {
                emptyIntermediateVec();
                std::cout << "-1" << endl;
                return 0;
            }
        }
    }

    if(atoi(intermediateInputVec[1].c_str()) == atoi(intermediateInputVec[3].c_str()) &&
            (atoi(intermediateInputVec[2].c_str()) == atoi(intermediateInputVec[4].c_str()))){
        ///check that the start point and end point aren't the same.
        emptyIntermediateVec();
        std::cout << "-1" << endl;
        return 0;
    }
    for(int i=0;i<8;i++){///push the input to the correct vector.
        tripInformationInput.push_back(intermediateInputVec[i]);
    }
    emptyIntermediateVec();
    return &tripInformationInput;///return the address of the vector as the output.
}


/*
 * the method recieves an input as a string trims it and checks if the input
 * is valid or not if it isn't is prints -1 else it returns a vector with the
 * propr input as elements inside of it.
 */
vector <string>*  InputValidator::validateInputForTaxi(){

    if(!intermediateInputVec.empty()){///empties the vector prior to the function.
        emptyIntermediateVec();
        emptyTheTripVec();
    }
    string taxiInput;
    int min;
    int max;
    std::cin.clear(); // clears error flags
    std::getline(std::cin, taxiInput);
    int therAreSpaces = checkIfThereAreSpaces(taxiInput);///check if there is an extra space in th input
    if(therAreSpaces == -1){
        std::cout << "-1" << endl;
        emptyIntermediateVec();///if so then the input is invalid.
        return 0;
    }
    emptyIntermediateVec();
    parseInputByDelimiter(taxiInput, ',');///splits the input into tokens by a comma.
    if(intermediateInputVec.size()!=4){/// if there are more than 4 elements then the input is invalid.
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    for(int i=0;i<2;i++){
        if( i == 0){///the id of the taxi

            min =0;///it must be non negative.
            max = -1;
        }else {///the type of the taxi
            min =1;///it mus be 1 or 2.
            max =2;
        }
        int num = checkIfIsAvalidNumber(intermediateInputVec[i], min, max);
        ///check if the number parts of the input are correct.
        if(num == -1){
            std::cout << "-1" << endl;
            emptyIntermediateVec();///else print -1.
            return 0;
        }
    }
    string man = intermediateInputVec[2];
    string color = intermediateInputVec[3];
    if(!(!man.compare("H") || !man.compare("S") || !man.compare("T") || !man.compare("F"))){
        ///check if the maunfaturer of the taxi is one of these kind.
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    if(!(!color.compare("R") || !color.compare("B") || !color.compare("G") || !color.compare("P")
                                                                        || !color.compare("W"))) {
        ///check if the color of the taxi is correct.
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    for(int i=0;i<4;i++){///push the elements into the proper vector.
        taxiInputVec.push_back(intermediateInputVec[i]);
    }
    emptyIntermediateVec();
    return &taxiInputVec;///return the vector.
}


/*
 * the method receives an input of a new driver, it gets an id of a driver.
 * the method checks if the id is inside of the drivers map using an iterator.
 * if it is it returns the id otherwise it returns -1.
 */
int InputValidator::validateInputForDriversLocation(map<int,Driver*> driversMap){
        if(!intermediateInputVec.empty()) {///empties the vector.
            emptyIntermediateVec();
        }
    string id;
    int driverId;
    int foundDriverFlag=0;
    std::cin.clear(); // clears error flags
    std::getline(std::cin, id);
    int thereAreSpaces = checkIfThereAreSpaces(id);/// validate that we have no spaces in the input.
    if(thereAreSpaces == -1){
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return -1;
    }
    driverId = checkIfIsAvalidNumber(id,0,-1);///validate that we have a number as an input that is greater then -1.
    if(driverId == -1) {
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return -1;
    }
    emptyIntermediateVec();
    map<int, Driver *>::iterator it;
    for (it = driversMap.begin(); it != driversMap.end(); it++){///validate that the driver is in the map by his id.
        if(it->first == driverId);
        foundDriverFlag =1;
    }
    if(foundDriverFlag == 0){/// if it isn't return -1.
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return -1;
    }
    return driverId;///else return the driver id.
}



/*
 * the method receives an input of a new driver, it runs checks that the input is valid.
 * if the input is invalid it returns null (0) otherwise it returns a vector with the input
 * as elements of the vector.
 */

vector <string>*  InputValidator::validateInputForNewDriver(){
    if(!intermediateInputVec.empty()) {///empties the vectors.
        emptyIntermediateVec();
    }
    int min;
    int max;
    string input;
    std::cin.clear(); // clears error flags
    std::getline(std::cin, input);///getting the input of the driver
    boost::algorithm::trim(input);
    int thereAreSpaces = checkIfThereAreSpaces(input);/// validate that we have no spaces in the input.
    if(thereAreSpaces == -1){
        emptyIntermediateVec();
        return 0;
    }
    emptyIntermediateVec();
    parseInputByDelimiter(input, ',');///split the input by comma
    if(intermediateInputVec.size()!=5){///check that indeed we have 5 elements.
        emptyIntermediateVec();
        return 0;
    }
    for(int i=0;i<5;i++){
        if(i!=2) {
            if (i !=1) {///verify that the numbers are greater than 0.
                min = 0;
                max = -1;
            } else {/// i=1 that means that the age of the driver must be greater than 0.
                min = 1;
                max = -1;
            }
            int num = checkIfIsAvalidNumber(intermediateInputVec[i], min, max);
            if (num == -1) {
                std::cout << "-1" << endl;
                emptyIntermediateVec();
                return 0;
            }
        } else {
            string status = intermediateInputVec[2];
            if(!(!status.compare("S") || !status.compare("M") || !status.compare("D") || !status.compare("W"))){
                ///checks if the marital status of the driver is one of these.
                emptyIntermediateVec();
                return 0;
            }
        }
    }
    for(int i=0;i<5;i++){///push the elements
        driverInputVec.push_back(intermediateInputVec[i]);
    }
    emptyIntermediateVec();///empty the vector.
    return &driverInputVec;///returns the address of the vector.
}