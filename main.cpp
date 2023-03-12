#include <iostream>
#include "networking/listener.h"
#include "networking/socketHandle.h"
using namespace std;


void OnConnect(socketHandle socketHandle){
    cout << "Client connected from " << socketHandle.ip << endl;
}

int main() {
    listener listener;

    listener.start("192.168.1.30", "4444");
    listener.onConnected = [](socketHandle handle) {
        OnConnect(handle);
    };
    return 0;
}


