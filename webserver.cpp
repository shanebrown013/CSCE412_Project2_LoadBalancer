
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

bool Webserver::checkStatus(Request *r, int *tableCount, ofstream &fw, double et, int timeRun) {

    this->current_time = chrono::system_clock::now();
    time_t tCurr = chrono::system_clock::to_time_t(this->current_time);
    time_t tStart = chrono::system_clock::to_time_t(start_time);

    auto end = chrono::system_clock::now();

    auto tCurrTemp = chrono::duration_cast<chrono::milliseconds>(end - this->start_time);

    //DEBUGGING TIMES
    // cout << "tCurr: " << tCurrTemp.count() << endl;
    // cout << "pTime + tStart: " << (r->processing_time + tStart) << endl;

    if (et > timeRun) {
        et = timeRun;
    }

    if (this->q == nullptr && tStart == 0) {
        addRequest(r);
        return true;
    } else {
        if (tCurrTemp.count() > (this->currentRequest.processing_time)) {
            fw << *tableCount << ".\t\tAt " << et << " clock cycles, Server " << currentRequest.serverName << " Proccessed request FROM " << currentRequest.ipIN << " TO " << currentRequest.ipOUT << " that had a processing time of " << currentRequest.processing_time << endl;
            (*tableCount)++;
            this->q = nullptr;
            addRequest(r);
            return true;
        }
    }

    return false;
}


bool Webserver::checkStatus2(int *tableCount, ofstream &fw, double et, int timeRun) {

    this->current_time = chrono::system_clock::now();
    time_t tCurr = chrono::system_clock::to_time_t(this->current_time);
    time_t tStart = chrono::system_clock::to_time_t(start_time);

    auto end = chrono::system_clock::now();

    auto tCurrTemp = chrono::duration_cast<chrono::milliseconds>(end - this->start_time);

    if (et > timeRun) {
        et = timeRun;
    }

    if (tCurrTemp.count() > (this->currentRequest.processing_time)) {
        fw << *tableCount << ".\t\tAt " << et << " clock cycles, Server " << currentRequest.serverName << " Proccessed request FROM " << currentRequest.ipIN << " TO " << currentRequest.ipOUT << " that had a processing time of " << currentRequest.processing_time << endl;
        (*tableCount)++;
        this->q = nullptr;
        this->start_time = chrono::system_clock::now() + chrono::hours(1000);
        return true;
    }

    return false;
}