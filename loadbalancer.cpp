#include <iostream>
#include <queue>
#include <vector>
#include <unistd.h>
#include <fstream>
#include "requests.h"
#include "webserver.h"

using namespace std;

/**
 * This class is to keep track of the time that is passed (similar to a stopwatch)
 */

class Timer{
public:

    /**
     * Start, or begin, the timer (stopwatch). 
     */
    void start(){
        startTime = chrono::system_clock::now();
        isRunning = true;
    }
    
    /**
     * Stop, or end, the timer (stopwatch). 
     */
    void stop(){
        endTime = chrono::system_clock::now();
        isRunning = false;
    }
    
    /**
     * Return the number of milliseconds that has passed since the timer was first started.
     */
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

    /**
     * Return the number of seconds that has passed since the timer was first started. 
     * This function calls the elaspedMilliseconds() function as well to perform its
     * calculation/conversion to seconds
     */
    double elapsedSeconds(){
        return elapsedMilliseconds() / 1000.0;
    }

private:
    chrono::time_point<chrono::system_clock> startTime; /**< Starting place/time the timer was started */
    chrono::time_point<chrono::system_clock> endTime; /**< Ending place/time the timer was stopped */
    bool isRunning; /**< True or False value that tracks if the timer is currently running or is currently stopped */
};


/**
 * The main load balancer fucntion that performs the load balancer duties. This function will
 * call the other classes, Webserver and Request, to simulate the load balancer. The user will be prompted to 
 * enter how many webservers they wish to create and how many clock cycles they would like the load balancer to
 * cycle through. The output for the load balancer will be written into a newly created file named, "LoadBalancerLog.txt"
 */
int main() {
    srand(time(NULL));

    // Get the number of servers from user
    int numOfServers = 0; /**< Number of webservers to create from user input */
    cout << "Enter the number of servers: ";
    cin >> numOfServers;

    int timeRun = 0; /**< Amount of cycles to run the load balancer through from user input */
    cout << "Enter the time you want to run the load balancer (clock cycles): ";
    cin >> timeRun;

    // Generate full queue
    queue<Request> requestqueue; /**< A queue of type Request that holds the generated requests */
    for (int i = 0; i < numOfServers*2; i++) {
        Request request;
        requestqueue.push(request);
    }

    // open file
    ofstream fw("LoadBalancerLog.txt"); /**< Outout file for the load balancer results */
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

    bool wsStatus = false; /**< Status that tells if the request at a specific webserver is completed */

    asciiValue = 65;
    int index = 0; /**< Index value used for iterating through webservers */
    int tableCount = 1; /**< Count integer used for output purposes */
    int *tableCountRef = &tableCount; /**< Reference pointer to tableCount */
    int newRequestIndexCount = 0; /**< Counter used to indicate when to random add new requests to the queue */ 

    Timer timer;
    timer.start();
    while (!requestqueue.empty() && (timer.elapsedMilliseconds() < timeRun)) {
        Request temp = requestqueue.front(); /**< Variable of type Request used to manipulate specific requests */
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

    // This function below prints the last [numOfServers] requests that are finishing in the load balancer
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