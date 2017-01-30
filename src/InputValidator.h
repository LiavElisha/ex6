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
    vector<int> matrixInput;///holds the parameter for building a matrix.
    vector<string> intermediateInputVec;///holds intermediate values for computation.
    vector<int> intermediateIntInput;///holds intermediate int values for computation.
    vector <string> tripInformationInput;///holds the parameters for the trip information.
    vector<string> taxiInputVec;///holds the paremeters for the cab.
    vector<string>driverInputVec;///holds the parameter for the driver.
    vector<string>doubleVec;///hods the parameter for checking a double.
public:

    /*
 * the method gets a string and a range which the string should be between.
 * first it checks if all of its components are digits and then it checks if the number is in the range given if
 * one is given.
 * if it isn't it returns -1 otherwise it returns the num.
 *
 */
    double checkIfIsAvalidDouble(string input, double min, double max);

    /*
  * the method gets a string and a range which the string should be between.
  * first it checks if all of its components are digits and then it checks if the number is in the range given if
  * one is given.
  * if it isn't it returns -1 otherwise it returns the num.
  *
  */
    int checkIfIsAvalidNumber(string input,int min, int max);


    /*
 * the method gets a string and a delimiter ands splits it into token where each token is pushed to a vector
 * of strings.
 */
    void parseInputByDelimiter(string input, char delimiter);

    /*
 * the method empties the vectors of string in case that the input was incorrect
 * and new input should be insrted.
 */
    void emptyIntermediateVec();



/*
 * the method empties the vector.
 */
    void emptyTheTripVec();

    /*
 * the method empties the vector.
 */
    void emptyTaxiInputVec();
    InputValidator();//constructor.

    /*
 * the method other method for splitting the input into tokens then it checks if each
 * parameter given is a number and then if it is then it inserts them into a vector of strings.
 * otherwise it receives a new input until it is correct.
 */
    void validateDimenstionOfMatrix();


    /*
 * the method verifies the the input was given as obstacles is valid it returns -1 if it isn't and 0 otherwise.
 * first it uses other methods to split the input into tokens by comma, then it checks if each component
 * is a number and if so that it is in the range of the matrix. if so it pushes the input into the input
 * vector.
 */
    int validateInputForObstacles();

    /*
 * the method verifies that the input given as matrix is valid, first it checks if the matrix dimension
 * are correct or not and then if the obstacles give.
 * if not it keeps getting input until it receives a valid input and if it is correct it returns
 * a vector of ints where the first parameter is the x dimension of the matrix, the second is the y dimension
 * the third is the number of obstacles and then each pair is an obstacle.
 */
    vector <int>*  validateInputForMatrix();


    /*
 * the method empties the vector of the matrix input .
 */
    void emptyTheMatrixVec();

    /*
 *  the method gets a string and parses it by the delimiter "space" =' ' and pushes it into a vector,
 *  if it has spaces that means that there are more than one element in the vector then it returns -1.
 *  else it returns 0.
 */
    int checkIfThereAreSpaces(string input);



    /*
 * the method gets as parameters the dimension of the matrix.
 * then it recieves an input from the user through the console and checks if the input was correct or not.
 * if the input is valid it returns a vector with its element as the input. else it return null.
 */

    vector <string>*  validateInputForTripInformation(int xDim, int yDim);

    /*
 * the method recieves an input as a string trims it and checks if the input
 * is valid or not if it isn't is prints -1 else it returns a vector with the
 * proper input as elements inside of it.
 */
    vector <string>*  validateInputForTaxi();


    /*
 * the method receives an input of a new driver, it gets an id of a driver.
 * the method checks if the id is inside of the drivers map using an iterator.
 * if it is it returns the id otherwise it returns -1.
 */
    int validateInputForDriversLocation(map<int,Driver*> driversMap);

    /*
 * the method receives an input of a new driver, it runs checks that the input is valid.
 * if the input is invalid it returns null (0) otherwise it returns a vector with the input
 * as elements of the vector.
 */

    vector <string>*  validateInputForNewDriver();


    /*
 * the method receives a number and checks if it is a valid number if it is it returns it
 * otherwise it returns -1.
 */
    int validateAmountOfDrivers();

    /*
 * the method gets as paramteres the trip vector and the id of the current trip.
 * then it checks if an other trip has the same id, if so the input is invalid and we return -1
 * after printing -1, otherwise we return the id of the trip/
 */
    int validateIdOfTrip(vector<TripInformation*> tripDeque, int id);


    /*
 * the method gets a vector of cabs and an id, then the method cheks if another cab in the vector,
 * has the same id, if so we print -1 and return -1.
 * otherwise we return the id.
 */
    int validateIdOfTaxi(vector<AbstractCab*> cabVector, int id);
};


#endif //EX6_INPUTVALIDATOR_H
