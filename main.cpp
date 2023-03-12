#include <iostream>
#include <vector>
#include "networking/socketEvents.h"
#include "networking/listener.h"
#include "networking/socketHandle.h"
using namespace std;


void OnConnect(const socketHandle& socketHandle){
    cout << "Client connected from " << socketHandle.ip << endl;
}

int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);

    string ip;
    string port;
    bool listen = false;
    bool connect = false;
    for (int i = 0; i < argc; i++) {
        if (args[i] == "-c") {
            connect = true;
        }
        else if (args[i] == "-l") {
            listen = true;
        }
        else if (args[i] == "-i" && i + 1 < argc) {
            ip = args[i + 1];
            i++;
        }
        else if (args[i] == "-p" && i + 1 < argc) {
            port = args[i + 1];
            i++;
        }
    }

    try{
        if(listen){
            listener listener;
            socketEvents::getInstance().setOnConnected([](socketHandle * handle) { OnConnect(*handle); } );

            listener.start(ip, port);

        }
        if(connect){
            socketHandle handle;
            socketEvents::getInstance().setOnConnected([](socketHandle * handle) { OnConnect(*handle);});
            handle.connect(ip, port);
        }
    }
    catch(const exception &ex){
        cerr << "Exception: " << ex.what() << endl;
    }

    return 0;
}


