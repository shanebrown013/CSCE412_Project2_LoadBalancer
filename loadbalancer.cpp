#include <iostream>
#include "requests.cpp"

using namespace std;

int main() {

    // Get the number of servers from user
    int numOfServers = 0;
    cout << "Enter the number of servers: ";
    cin >> numOfServers;

    int timeRun = 0;
    cout << "Enter the time you want to run the load balancer (seconds): ";
    cin >> timeRun;

    // TEST
    Request test;
    test.generateIP();
    
}