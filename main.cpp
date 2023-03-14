#include <iostream>
#include <vector>
#include "networking/socketEvents.h"
#include "networking/listener.h"
#include "networking/socketHandle.h"
#include "networking/networkMessage.pb.h"
#include "resolver.h"
using namespace std;


void OnConnect(const socketHandle& socketHandle){
    cout << "Connection accepted from " << socketHandle.ip << endl;
}
void OnDisconnect(const socketHandle& socketHandle){
    cout << "Disconnection detected from " << socketHandle.ip << endl;
}
void OnReady(socketHandle & socketHandle, bool initiator){
    protobufMessage pm;
    if (initiator){
        pm.mutable_examplemessage()->set_message("On ready event proc and on receive event proc test.");
    }
    else {
        pm.mutable_examplemessage()->set_message("listener has sent this.");
    }
    socketHandle.send(pm);
}
void OnReceive(socketHandle & socketHandle, protobufMessage & message){
    resolver::execute(socketHandle, message);
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
        socketEvents::getInstance().setOnConnected([](socketHandle * handle) { OnConnect(*handle); } );
        socketEvents::getInstance().setOnDisconnected([](socketHandle * handle) { OnDisconnect(* handle);});
        socketEvents::getInstance().setOnReady([](socketHandle * handle, bool initiator) { OnReady(*handle, initiator);});
        socketEvents::getInstance().setOnReceive([](socketHandle * handle, protobufMessage * message) { OnReceive(*handle, *message);});
        if(listen){
            listener listener;
            listener.start(ip, port);
        }
        if(connect){
            socketHandle handle;
            handle.connect(ip, port);
        }
    }
    catch(const exception &ex){
        cerr << "Exception: " << ex.what() << endl;
    }
    cout << "End of main thread, press enter to continue...";
    cin.ignore();

    return 0;
}


