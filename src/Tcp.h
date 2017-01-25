/************************************************************
* File description: TCP header file. the class inherit from	*
* socket. methods of tcp socket type						*
************************************************************/

#ifndef EX11_TCP_H
#define EX11_TCP_H


#include "Socket.h"

class Tcp: public Socket {
private:
    int descriptorCommunicateClient;
public:
    /***********************************************************************
    * function name: Tcp												   *
    * The Input: Boolean, true - if server, false if client and port number*
    * The output: none										               *
    * The Function operation: creating new Tcp						       *
    ***********************************************************************/
    Tcp(bool isServers, int port_num);
    /***********************************************************************
    * function name: ~Tcp												   *
    * The Input: none													   *
    * The output: none										               *
    * The Function operation: default destructor					       *
    ***********************************************************************/
    virtual ~Tcp();
/***********************************************************************
	* function name: initialize											   *
	* The Input: none              										   *
	* The output: int number representing the return status		           *
	* The Function operation: initialize the Socket object and getting a   *
	* socket descriptor.												   *
	***********************************************************************/
    int initialize();

    /***********************************************************************
    * function name: acceptNewClient									   *
    * The Input: get new client							           		   *
    * The output: the number that return from the accept		           *
    * The Function operation: sending the required data, using his length  *
    * and the socket descroptor											   *
    ***********************************************************************/
    int openNewClient();
    /***********************************************************************
    * function name: sendData											   *
    * The Input: string representing the data to send		               *
    * The output: int number representing the return status		           *
    * The Function operation: sending the input data to the socket         *
    * who connect to this socket. 										   *
    ***********************************************************************/
    int sendData(string data, int communication);
    /***********************************************************************
    * function name: recive	`											   *
    * The Input: none										               *
    * The output: int number representing the return status	               *
    * The Function operation: getting data from the other socket and print *
    * the data															   *
    ***********************************************************************/
    int reciveData(char* buffer, int size, int communication);
};



#endif //EX11_TCP_H
