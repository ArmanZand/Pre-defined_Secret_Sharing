#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>


#include "networking/socketEvents.h"
#include "networking/listener.h"
#include "networking/socketHandle.h"
#include "networking/networkMessage.pb.h"
#include "resolver.h"

#include "cryptography/cryptoUtilities.h"
#include "cryptography/polynomial.h"
#include "bignum.h"

void OnConnect(socketHandle * handlePtr){
    handleTracker::add(handlePtr);
    cout << "Connection accepted from " << handlePtr->ip << endl;
}
void OnDisconnect(socketHandle * handlePtr){
    handleTracker::remove(handlePtr);
    cout << "Disconnection detected from " << handlePtr->ip << endl;
}
void OnReady(socketHandle * handlePtr, bool initiator){
    if(initiator){
        protobufMessage pm;
        pm.mutable_nodeinfo()->set_id(get<bignum>(config["NODE_ID"]).toStr());
        pm.mutable_nodeinfo()->set_name(get<string>(config["NODE_NAME"]));
        pm.mutable_nodeinfo()->set_type(static_cast<nodeType>(get<int>(config["NODE_TYPE"])));
        handlePtr->send(pm);
    }

}
void OnReceive(socketHandle * handlePtr, protobufMessage & message){
    resolver::execute(handlePtr, message);
}


int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    string configPath;
    for(int i = 0; i < argc; i++){
        if (args[i] == "-c" && i + 1 < argc) {
            configPath = args[i+1];
            i++;
        }
    }
    try{

        socketEvents::getInstance().setOnConnected([](socketHandle * handle) { OnConnect(handle); } );
        socketEvents::getInstance().setOnDisconnected([](socketHandle * handle) { OnDisconnect(handle);});
        socketEvents::getInstance().setOnReady([](socketHandle * handle, bool initiator) { OnReady(handle, initiator);});
        socketEvents::getInstance().setOnReceive([](socketHandle * handle, protobufMessage * message) { OnReceive(handle, *message);});

        if(!empty(configPath)){
            parameters::loadConfig(configPath);
        }
        unique_ptr<thread> waitingFor;
        if(parameters::keyExists("LISTENER_START")){
            string address = get<string>(config["LISTENER_START"]);
            int delimiter = address.find(":");
            string ip = address.substr(0, delimiter);
            string port = address.substr(delimiter+1);
            listener listener;
            waitingFor = listener.start(ip, port);
        }
        if(parameters::keyExists("AUTO_CONNECT")){
            stringstream ss(get<string>(config["AUTO_CONNECT"]));
            string address;
            while(getline(ss, address, ',')){
                int delimiter = address.find(":");
                string ip = address.substr(0, delimiter);
                string port = address.substr(delimiter+1);
                socketHandle * handlePtr = new socketHandle();
                waitingFor = handlePtr->connect(ip, port);

            }
        }
        if(waitingFor->joinable()){
        waitingFor->join();}
    }
    catch(const exception &ex){
        cerr << "Exception: " << ex.what() << endl;
    }
    cout << "End of main thread, press enter to continue...";
    cin.ignore();
    return 0;
}


