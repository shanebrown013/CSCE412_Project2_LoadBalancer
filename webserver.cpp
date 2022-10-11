
#include "webserver.h"
#include "requests.h"


Webserver::Webserver(char name) {
    this->wName = name;
    this->q = nullptr;
}

void Webserver::addRequest(Request *r) {

    // Add request to server
    r->serverName = this->wName;
    this->currentRequest = *r;
    this->q = &currentRequest;
    // New start time for added request
    this->start_time = chrono::system_clock::now();

}

bool Webserver::checkStatus(Request *r, int *tableCount) {

    this->current_time = chrono::system_clock::now();
    time_t tCurr = chrono::system_clock::to_time_t(this->current_time);
    time_t tStart = chrono::system_clock::to_time_t(start_time);

    //DEBUGGING TIMES
    // cout << "tCurr: " << tCurr << endl;
    // cout << "pTime + tStart: " << (r->processing_time + tStart) << endl;

    if (this->q == nullptr && tStart == 0) {
        addRequest(r);
        // return true;
    } else {
        if (tCurr > (this->currentRequest.processing_time + tStart)) {
            cout << *tableCount << "\t\t" << currentRequest.serverName << "\t\t" << currentRequest.ipIN << "\t\t" << currentRequest.ipOUT << "\t\t" << currentRequest.processing_time << endl;
            (*tableCount)++;
            this->q = nullptr;
            addRequest(r);
            return true;
        }
    }

    return false;
}
