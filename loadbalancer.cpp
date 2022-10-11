#include <iostream>
#include <queue>
#include <vector>
#include <unistd.h>
#include "requests.h"
#include "webserver.h"

using namespace std;

int main() {
    srand(time(NULL));

    // Get the number of servers from user
    int numOfServers = 0;
    cout << "Enter the number of servers: ";
    cin >> numOfServers;

    int timeRun = 0;
    cout << "Enter the time you want to run the load balancer (seconds): ";
    cin >> timeRun;

    // Generate full queue
    queue<Request> requestqueue;
    for (int i = 0; i < numOfServers*2; i++) {
        Request request;
        requestqueue.push(request);
    }

    // create webservers
    vector<Webserver> ws;
    int asciiValue = 65;
    cout << "Webservers:" << endl;
    for (int i = 0; i < numOfServers; i++) {
        Webserver server((char)asciiValue);
        asciiValue++;
        cout << server.wName << endl;
        ws.push_back(server);
    }
    cout << endl << endl;

    bool wsStatus = false;

    // print out table format
    cout << "Count\t\tServer\t\tIP IN (From)\t\tIP OUT (To)\t\tProcess Time" << endl;

    asciiValue = 65;
    int index = 0;
    int tableCount = 1;
    int *tableCountRef = &tableCount;
    int newRequestIndexCount = 0;
    while (!requestqueue.empty()) {
        Request temp = requestqueue.front();
        requestqueue.pop();
        while (wsStatus == false) {
                if (ws.at(index).wName == (char)asciiValue) {
                    wsStatus = ws.at(index).checkStatus(&temp, tableCountRef);
                    sleep(1);
                    asciiValue++;
                } else {
                    asciiValue = 65;
                }
                if (index + 1 == ws.size()) {
                    index = 0;
                } else {
                    index++;
                }
            // if (newRequestIndexCount % 222 == 0) {
            //     Request request;
            //     requestqueue.push(request);
            // }
        }
        // cout << "HERE" << endl;
        wsStatus = false;
    }

    int finishCount = 0;
    bool complete = false;
    index = 0;
    while (complete == false) {
        // go through all webservers and see if the *q is nullptr
        complete = ws.at(index).checkStatus2(tableCountRef);
        sleep(1);
        if (complete) {
            finishCount++;
        }
        if (finishCount == numOfServers) {
            complete = true;
            break;
        } else {
            complete = false;
        }
        if (index + 1 == ws.size()) {
            index = 0;
        } else {
            index++;
        }
    }

}