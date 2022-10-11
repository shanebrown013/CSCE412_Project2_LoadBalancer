#include <iostream>
#include <queue>
#include <vector>
#include <unistd.h>
#include <fstream>
#include "requests.h"
#include "webserver.h"

using namespace std;

class Timer{
public:
    void start(){
        startTime = chrono::system_clock::now();
        isRunning = true;
    }
    
    void stop(){
        endTime = chrono::system_clock::now();
        isRunning = false;
    }
    
    double elapsedMilliseconds(){
        chrono::time_point<chrono::system_clock> endTime;
        if(isRunning){
            endTime = chrono::system_clock::now();
        }
        else{
            endTime = endTime;
        }
        return chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    }

    double elapsedSeconds(){
        return elapsedMilliseconds() / 1000.0;
    }

private:
    chrono::time_point<chrono::system_clock> startTime;
    chrono::time_point<chrono::system_clock> endTime;
    bool isRunning;
};

int main() {
    srand(time(NULL));

    // Get the number of servers from user
    int numOfServers = 0;
    cout << "Enter the number of servers: ";
    cin >> numOfServers;

    int timeRun = 0;
    cout << "Enter the time you want to run the load balancer (clock cycles): ";
    cin >> timeRun;

    // Generate full queue
    queue<Request> requestqueue;
    for (int i = 0; i < numOfServers*2; i++) {
        Request request;
        requestqueue.push(request);
    }

    // open file
    ofstream fw("LoadBalancerLog.txt");
    if (!fw.is_open()) {
        cout << "Can not create log. Exiting..." << endl;
        exit(1);
    }
    ofstream *fwRef = &fw;

    // create webservers
    vector<Webserver> ws;
    int asciiValue = 65;
    fw << "\nWebservers:" << endl;
    for (int i = 0; i < numOfServers; i++) {
        Webserver server((char)asciiValue);
        asciiValue++;
        fw << server.wName << endl;
        ws.push_back(server);
    }
    fw << endl;

    fw << "Initial Queue Size: " << requestqueue.size() << endl;
    fw << "The requests have a random process time of 2-500 per request\nNumber of requests added per random cycles range from 1 - numOfServers * 2 every 10 clock cycles." << endl;

    bool wsStatus = false;

    asciiValue = 65;
    int index = 0;
    int tableCount = 1;
    int *tableCountRef = &tableCount;
    int newRequestIndexCount = 0;

    Timer timer;
    timer.start();
    while (!requestqueue.empty() && (timer.elapsedMilliseconds() < timeRun)) {
        Request temp = requestqueue.front();
        requestqueue.pop();
        while (wsStatus == false) {
                if (ws.at(index).wName == (char)asciiValue) {
                    wsStatus = ws.at(index).checkStatus(&temp, tableCountRef, *fwRef, timer.elapsedMilliseconds(), timeRun);
                    asciiValue++;
                } else {
                    asciiValue = 65;
                }
                if (index + 1 == ws.size()) {
                    index = 0;
                } else {
                    index++;
                }
        }
        if (newRequestIndexCount % 10 == 0) {
            // add a new request every 10th run
            int randNum = rand() % (numOfServers*2 - 1) + 1;
            for (int i = 0; i < randNum; i++) {
                Request request;
                requestqueue.push(request);
            }
        }
        newRequestIndexCount++;
        wsStatus = false;
    }

    int finishCount = 0;
    bool complete = false;
    index = 0;
    while (complete == false) {
        // go through all webservers and see if the *q is nullptr
        complete = ws.at(index).checkStatus2(tableCountRef, *fwRef, timer.elapsedMilliseconds(), timeRun);
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

    if (requestqueue.size() == 0) {
        fw << "All requests were processed at " << timer.elapsedMilliseconds() << endl << endl;
    }
    fw << "\nExisting Request Queue: " << requestqueue.size() << endl;
    cout << "\nExisting Request Queue: " << requestqueue.size() << endl;

}