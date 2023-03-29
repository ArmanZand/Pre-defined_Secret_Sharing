//
// Created by arman on 14/03/2023.
//
#include <functional>
#include "resolver.h"


using commandHandler = function<void(socketHandle &, protobufMessage &)>;
unordered_map<protobufMessage::CommandCase, commandHandler> commands = {
        { protobufMessage::kNodeInfo, resolver::nodeInfo },
        { protobufMessage::kNodeInfoReply, resolver::nodeInfoReply },
        { protobufMessage::kNodePayload, resolver::nodePayload },
        { protobufMessage::kShare, resolver::share }
};
void resolver::execute(socketHandle &handle, protobufMessage &pm) {
    try {
        auto it = commands.find(pm.command_case());
        if(it != commands.end()){
            it->second(handle, pm);
        }
        else {
            throw runtime_error("Command not recognised.");
        }
    }
    catch(exception & ex){
        cerr << ex.what() << endl;
    }
}
void resolver::nodeInfo(socketHandle &handle, protobufMessage &pm){
    handle.name = pm.nodeinfo().name();
    handle.id = bignum::parseStr(pm.nodeinfo().id().c_str());
    cout << "Discovered Node Info for " << handle.ip << ":" << endl;
    cout << "\tName: " << handle.name << endl;
    cout << "\tId: " << handle.id.toStr() << endl;
    protobufMessage rm;
    string nodeId = get<bignum>(config["NODE_ID"]).toStr();
    string nodeName = get<string>(config["NODE_NAME"]);
    rm.mutable_nodeinforeply()->set_id(nodeId);
    rm.mutable_nodeinforeply()->set_name(nodeName);
    handle.send(rm);
}

void resolver::nodeInfoReply(socketHandle &handle, protobufMessage &pm){
    handle.name = pm.nodeinforeply().name();
    handle.id = bignum::parseStr(pm.nodeinforeply().id().c_str());
    cout << "Discovered Node Info for " << handle.ip << ":" << endl;
    cout << "\tName: " << handle.name << endl;
    cout << "\tId: " << handle.id.toStr() << endl;
}

void resolver::nodePayload(socketHandle &handle, protobufMessage &pm) {

}

void resolver::share(socketHandle &handle, protobufMessage &pm) {

}


//void resolver::exampleMessage(socketHandle &handle, protobufMessage &pm) {
//    cout << handle.ip << "> " << pm.examplemessage().message() << endl;
//}
