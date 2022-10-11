#ifndef REQUESTS_H
#define REQUESTS_H

#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include <unistd.h>

using namespace std;

class Request {
    public:
        string ipIN;
        string ipOUT;
        int processing_time;
        string serverName;

        //functions
        Request();
};

#endif