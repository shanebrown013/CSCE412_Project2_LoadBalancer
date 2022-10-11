
#include "requests.h"

Request::Request() {
    for (int j = 0; j < 2; j++) {
        string tempIP = "";
        int num = 0;
        for (int i = 0; i < 4; i++) {
            // run 4 times
            num = rand() % 255;
            tempIP = tempIP + to_string(num) + ".";
        }
        tempIP = tempIP.substr(0, tempIP.length()-1);
        if (j == 0) {
            // populate this.ipIN
            this->ipIN = tempIP;
        } else if (j == 1) {
            // populate ipOUT
            this->ipOUT = tempIP;
        }
    }
    // Generate random process time
    int pTime = rand() % 9 + 2;
    this->processing_time = pTime;

    this->serverName = "";
}
