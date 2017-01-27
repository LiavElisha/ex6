//
// Created by yoav on 26/01/17.
//

#include <limits>
#include "InputValidator.h"


InputValidator::InputValidator(){

}


/*
 * the method validates through the functionality of the cin that the dimension of the matrix are ok.
 */



void InputValidator::parseInputByDelimiter(string input, char delimiter){
    string token;
    istringstream iss(input);
    while (getline(iss, token, delimiter)) {
        intermediateInputVec.push_back(token);
    }
}


int InputValidator::getAPositiveNumber() {
    int number;
    std::cin >> number;//get the input.
    if (std::cin.fail()) {
        std::cin.clear(); // clears error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//clear everything until the \n.
        std::cout << "-1" << endl;
        return -1;
    } else {
        if (number <= 0 || number>1000) {
            std::cout << "-1" << endl;
            return -1;
        } else {
            return number;
        }
    }
}


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

    if(tempNum> max || tempNum<min){
        return -1;
    }
    return tempNum;
}
void InputValidator::emptyIntermediateVec(){
    while(!intermediateInputVec.empty()){
        intermediateInputVec.pop_back();
    }
    while(!intermediateIntInput.empty()){
        intermediateIntInput.pop_back();
    }
}


void InputValidator::validateDimenstionOfMatrix(){
    int isValid = 0;
    string dimensions;
    int validNum;
    while(isValid!=1) {
        std::cin.clear(); // clears error flags
        std::getline(std::cin, dimensions);
        parseInputByDelimiter(dimensions, ' ');
        if(intermediateInputVec.size()==2) {
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





int InputValidator::validateInputForObstacles() {
    string obstacle;
    string token;
    string  numberOfObstacles;
    int amountOfObstacles;
    int isValid = 0;
    int validNum;
        std::cin.clear(); // clears error flags
        std::getline(std::cin, numberOfObstacles);
        parseInputByDelimiter(numberOfObstacles,' ');
        if(intermediateInputVec.size()!=1) {
            std::cout << "-1" << endl;
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
                int xVal = checkIfIsAvalidNumber(intermediateInputVec[0],1,matrixInput[1]);
                int yVal = checkIfIsAvalidNumber(intermediateInputVec[1],1,matrixInput[0]);
                if (xVal == -1 || yVal == -1) {
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