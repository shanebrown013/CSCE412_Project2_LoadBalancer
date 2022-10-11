#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <queue>
#include <unistd.h>
#include "requests.h"

using namespace std;

class Webserver {
    public: 
        char wName;
        chrono::system_clock::time_point start_time;
        chrono::system_clock::time_point current_time;
        Request currentRequest;
        Request *q;

        //functions
        Webserver(char name);
        void addRequest(Request *r);
        bool checkStatus(Request *r, int *tableCount);

};

#endif