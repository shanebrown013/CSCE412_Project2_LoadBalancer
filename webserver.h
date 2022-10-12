#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <queue>
#include <fstream>
#include <unistd.h>
#include "requests.h"

using namespace std;

/**
 * Webserver class refers to everything involving requests. This serves as a object that includes
 * wName, start_time, current_time, currentRequest, and *q.
 */
class Webserver {
    public: 
        char wName; /**< The name of the webserver (uses the capital alphabet) */
        chrono::system_clock::time_point start_time; /**< The starting time when a request gets added to a web server */
        chrono::system_clock::time_point current_time; /**< Current time from when the request was added to the webserver */
        Request currentRequest; /**< Request object that keeps track of the current request on a specific webserver */
        Request *q; /**< Request pointer that helps make sure the webserver is not on a current request throughout the process */

        //functions

        /**
         * Constructor for the webserver class that sets the default values for the attributes
         * 
         * @param name The character that represents the Webserver name.
         */
        Webserver(char name);

        /**
         * Adds a request to the available webserver. This function sets the server name for the specific
         * request, sets the current request, sets *q, and sets the start time when the request is added.
         * 
         * @param r Pointer/reference to the Request that is being processed/managed.
         */
        void addRequest(Request *r);

        /**
         * Checks the status of a specific webserver. Makes sure the current request in the specific webserver is completed 
         * before exchanging the request for a new one. If the request is completed on the specific
         * webserver, it will output a statement to the output file then replace the request with the new one
         * 
         * @param r Pointer/reference to the Request that is being processed/managed.
         * @param tableCount Number that helps iterate number of completed request to output file.
         * @param fw Pass by reference of the ofstream object to write to the output file.
         * @param et Value of when the process was completed
         * @param timeRun User-input value of how many clock cycles the load balancer will run.
         */
        bool checkStatus(Request *r, int *tableCount, ofstream &fw, double et, int timeRun);

        /**
         * Similar to checkStatus(). Checks the status of a specific webserver. Makes sure the current request in the specific webserver is completed.
         * If the request is completed on the specific
         * webserver, it will output a statement to the output file. but NOT add/replace a new request.
         * 
         * @param tableCount Number that helps iterate number of completed request to output file.
         * @param fw Pass by reference of the ofstream object to write to the output file.
         * @param et Value of when the process was completed
         * @param timeRun User-input value of how many clock cycles the load balancer will run.
         */
        bool checkStatus2(int *tableCount, ofstream &fw, double et, int timeRun);

};

#endif