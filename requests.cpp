#include <iostream>

using namespace std;

class Request {
    public:
        string ipIN;
        string ipOUT;
        int processTime;

        //functions
        void generateIP();
};

void Request::generateIP() {
    srand(time(NULL));
    string tempIP = "";
    int num = 0;
    for (int i = 0; i < 4; i++) {
        // run 4 times
        num = rand() % 255;
        tempIP = tempIP + to_string(num) + ".";
    }
    tempIP = tempIP.substr(0, tempIP.length()-1);
    cout << "TEST: " << tempIP << endl;
}