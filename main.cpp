#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "networking/socketEvents.h"
#include "networking/listener.h"
#include "networking/socketHandle.h"
#include "networking/networkMessage.pb.h"
#include "resolver.h"

#include "cryptography/polynomial.h"
#include "bignum/bignum.h"
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

    bignum prime("97");
    polynomial p(&prime);
    vector<point> points = { point(0, 5), point(1,10), point(2,20) };
    vector<bignum> coeffs = p.interpolate(points);

    vector<string> args(argv, argv + argc);
    string configPath;
    for(int i = 0; i < argc; i++){
        if (args[i] == "-c" && i + 1 < argc) {
            configPath = args[i+1];
            i++;
        }
    }
    try{
        if(!empty(configPath)){
        parameters::loadConfig(configPath);
        }
        socketEvents::getInstance().setOnConnected([](socketHandle * handle) { OnConnect(*handle); } );
        socketEvents::getInstance().setOnDisconnected([](socketHandle * handle) { OnDisconnect(* handle);});
        socketEvents::getInstance().setOnReady([](socketHandle * handle, bool initiator) { OnReady(*handle, initiator);});
        socketEvents::getInstance().setOnReceive([](socketHandle * handle, protobufMessage * message) { OnReceive(*handle, *message);});
        if(parameters::keyExists("LISTENER_START")){
            string address = get<string>(config["LISTENER_START"]);
            int delimiter = address.find(":");
            string ip = address.substr(0, delimiter);
            string port = address.substr(delimiter+1);
            listener listener;
            listener.start(ip, port);
        }
        if(parameters::keyExists("AUTO_CONNECT")){
            stringstream ss(get<string>(config["AUTO_CONNECT"]));
            string address;
            while(getline(ss, address, ',')){
                int delimiter = address.find(":");
                string ip = address.substr(0, delimiter);
                string port = address.substr(delimiter+1);
                socketHandle handle;
                handle.connect(ip, port);
            }
        }
    }
    catch(const exception &ex){
        cerr << "Exception: " << ex.what() << endl;
    }
    cout << "End of main thread, press enter to continue...";
    cin.ignore();
    return 0;
}


