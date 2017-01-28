//
// Created by yoav on 26/01/17.
//

#include <limits>
#include "InputValidator.h"


InputValidator::InputValidator(){

}


/*
 * the method gets a string and a delimiter ands splits it into token where each token is pushed to a vector
 * of strings.
 */
void InputValidator::parseInputByDelimiter(string input, char delimiter){
    string token;
    istringstream iss(input);
    while (getline(iss, token, delimiter)) {
        intermediateInputVec.push_back(token);
    }
}



/*
 * the method gets a string and a range which the string should be between.
 * first it checks if all of its components are digits and then it checks if the number is in the range given if
 * one is given.
 * if it isn't it returns -1 otherwise it returns the num.
 *
 */
int InputValidator::checkIfIsAvalidNumber(string input,int min, int max){
    unsigned long length = input.size();
    int tempNum= 0;
    for (int i=0;i<length;i++){
        if(isdigit(input[i])){
            tempNum = 10*tempNum+(input[i]-'0');
        } else{
            return -1;
        }
    }

    if(min!=-1){
        if (tempNum < min) {
            return -1;
        }
    }
    if(max!= -1){
        if (tempNum > max) {
            return -1;
        }
    }
    return tempNum;
}

/*
 *
 */

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
    while(isValid!=1) {
        std::cin.clear(); // clears error flags
        std::getline(std::cin, dimensions);
        parseInputByDelimiter(dimensions, ' ');
        if(intermediateInputVec.size() == 2) {
            for (int i = 0; i < 2; i++) {
                validNum = checkIfIsAvalidNumber(intermediateInputVec[i], 1, 1000);
                if (validNum == -1) {
                    emptyIntermediateVec();
                    std::cout << "-1" << endl;
                    break;
                } else {
                    intermediateIntInput.push_back(validNum);
                }
            }
            if (intermediateIntInput.size() == 2) {
                isValid = 1;
            }
        }else {
            emptyIntermediateVec();
            std::cout << "-1" << endl;
        }

    }
    matrixInput.push_back(intermediateIntInput[0]);
    matrixInput.push_back(intermediateIntInput[1]);
    emptyIntermediateVec();
}


/*
 *  the method gets a string and parses it by the delimiter "space" =' ' and pushes it into a vector,
 *  if it has spaces that means that there are more than one element in the vector then it returns -1.
 *  else it returns 0.
 */

int InputValidator::checkIfThereAreSpaces(string input){
    parseInputByDelimiter(input,' ');
    if(intermediateInputVec.size()!=1) {
        std::cout << "-1" << endl;
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
        std::getline(std::cin, numberOfObstacles);
        int thereAreSpaces = checkIfThereAreSpaces(numberOfObstacles);
        if(thereAreSpaces == -1){
            return -1;
        }
        amountOfObstacles = checkIfIsAvalidNumber(numberOfObstacles,0,matrixInput[0]*matrixInput[1]);
        if(amountOfObstacles == -1) {
            std::cout << "-1" << endl;
            return -1;
        }
    emptyIntermediateVec();
    std::cin.clear(); // clears error flags
    matrixInput.push_back(amountOfObstacles);
    for (int i = 0; i < amountOfObstacles; i++) {
        std::getline(std::cin, obstacle);
        parseInputByDelimiter(obstacle,' ');
        if (intermediateInputVec.size() != 1) {
            std::cout << "-1" << endl;
            return -1;
        } else {
            obstacle = intermediateInputVec.front();
            emptyIntermediateVec();
            parseInputByDelimiter(obstacle,',');
            if (intermediateInputVec.size() != 2) {
                std::cout << "-1" << endl;
                return -1;
            } else {
                int xVal = checkIfIsAvalidNumber(intermediateInputVec[0],0,matrixInput[1]-1);
                int yVal = checkIfIsAvalidNumber(intermediateInputVec[1],0,matrixInput[0]-1);
                if ((xVal == -1 || yVal == -1)|| (xVal ==0 && yVal == 0)) {
                    std::cout << "-1" << endl;
                    return -1;
                }else {
                    matrixInput.push_back(xVal);
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
    if(!intermediateInputVec.empty()){
        emptyIntermediateVec();
        emptyTheTripVec();
    }
    string input;
    int min;
    int max;
    std::cin.clear(); // clears error flags
    std::getline(std::cin, input);
    int therAreSpaces = checkIfThereAreSpaces(input);
    if(therAreSpaces == -1){
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
        if (i > 0 && i < 5) {// the points should be in the range of the matrix.
            if (i % 2 == 0) {
                min = 0;
                max = xDim - 1;
            } else {
                min = 0;
                max = yDim - 1;
            }
        }else if (i == 0) {  // the id should be bigger the 0.
            min = 0;
            max = -1;
        } else {//the tariff, the passanger amount and the time should all be bigger than 1.
            min = 1;
            max = -1;
        }
        int num = checkIfIsAvalidNumber(intermediateInputVec[i], min, max);
        if (num == -1) {
            emptyIntermediateVec();
            std::cout << "-1" << endl;
            return 0;
        }
    }

    if(atoi(intermediateInputVec[1].c_str()) == atoi(intermediateInputVec[3].c_str()) &&
            (atoi(intermediateInputVec[2].c_str()) == atoi(intermediateInputVec[4].c_str()))){
        emptyIntermediateVec();
        std::cout << "-1" << endl;
        return 0;
    }
    for(int i=0;i<8;i++){
        tripInformationInput.push_back(intermediateInputVec[i]);
    }
    emptyIntermediateVec();
    return &tripInformationInput;
}


vector <string>*  InputValidator::validateInputForTaxi(){

    if(!intermediateInputVec.empty()){
        emptyIntermediateVec();
        emptyTheTripVec();
    }
    string taxiInput;
    int min;
    int max;
    std::cin.clear(); // clears error flags
    std::getline(std::cin, taxiInput);
    int therAreSpaces = checkIfThereAreSpaces(taxiInput);
    if(therAreSpaces == -1){
        emptyIntermediateVec();
        return 0;
    }
    emptyIntermediateVec();
    parseInputByDelimiter(taxiInput, ',');
    if(intermediateInputVec.size()!=4){
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    for(int i=0;i<2;i++){
        if( i == 0){

            min =0;
            max = -1;
        }else {
            min =1;
            max =2;
        }
        int num = checkIfIsAvalidNumber(intermediateInputVec[i], min, max);
        if(num == -1){
            std::cout << "-1" << endl;
            emptyIntermediateVec();
            return 0;
        }
    }
    string man = intermediateInputVec[2];
    string color = intermediateInputVec[3];
    if(!(!man.compare("H") || !man.compare("S") || !man.compare("T") || !man.compare("F"))){
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    if(!(!color.compare("R") || !color.compare("B") || !color.compare("G") || !color.compare("P")
                                                                        || !color.compare("W"))) {
        std::cout << "-1" << endl;
        emptyIntermediateVec();
        return 0;
    }
    for(int i=0;i<4;i++){
        taxiInputVec.push_back(intermediateInputVec[i]);
    }
    emptyIntermediateVec();
    return &taxiInputVec;
}



int InputValidator::validateInputForDriversLocation(map<int,Driver*> driversMap){
        if(!intermediateInputVec.empty()) {
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
    driverId = checkIfIsAvalidNumber(id,0,-1);///validate that we have a number as an input that is greate the -1.
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

vector <string>*  InputValidator::validateInputForNewDriver(){
    if(!intermediateInputVec.empty()) {
        emptyIntermediateVec();
    }
    int min;
    int max;
    string input;
    std::cin.clear(); // clears error flags
    std::getline(std::cin, input);
    int thereAreSpaces = checkIfThereAreSpaces(input);/// validate that we have no spaces in the input.
    if(thereAreSpaces == -1){
        emptyIntermediateVec();
        return 0;
    }
    emptyIntermediateVec();
    parseInputByDelimiter(input, ',');
    if(intermediateInputVec.size()!=5){
        emptyIntermediateVec();
        return 0;
    }
    for(int i=0;i<5;i++){
        if(i!=2) {
            if (i == 0 || i==4) {
                min = 0;
                max = -1;
            } else {
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
                emptyIntermediateVec();
                return 0;
            }
        }
    }
    for(int i=0;i<5;i++){
        driverInputVec.push_back(intermediateInputVec[i]);
    }
    emptyIntermediateVec();
    return &driverInputVec;
}