#ifndef REQUESTS_H
#define REQUESTS_H

#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include <unistd.h>

using namespace std;

/**
 * Request class refers to everything involving requests. This serves as a object with 
 * ipIN, ipOUT, processing_time, and the serverName
 */
class Request {
    public:
        string ipIN; /**< Randomly generated IP address that is receiving (IN) the request process */ 
        string ipOUT; /**< Randomly generated IP address that is sending (OUT) the request process */ 
        int processing_time; /**< Randomly generated number that refers to how long it takes a request to fully/successfully complete*/ 
        string serverName; /**< Webserver name that the request is assigned to */ 

        //functions
        /**
         * Constructor for the Request class that generates the random ipIN, ipOUT, and processing times. 
         * Also, sets the default value for serverName.
         */
        Request();
};

#endif