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
    handle.type = pm.nodeinfo().type();
    cout << "Discovered Node Info for " << handle.ip << ":" << endl;
    cout << "\tName: " << handle.name << endl;
    cout << "\tId: " << handle.id.toStr() << endl;
    cout << "\tType: " << nodeTypeNames[handle.type]  << endl;
    protobufMessage rm;
    rm.mutable_nodeinforeply()->set_id(get<bignum>(config["NODE_ID"]).toStr());
    rm.mutable_nodeinforeply()->set_name(get<string>(config["NODE_NAME"]));
    rm.mutable_nodeinforeply()->set_type(static_cast<nodeType>(get<int>(config["NODE_TYPE"])));
    handle.send(rm);
}

void resolver::nodeInfoReply(socketHandle &handle, protobufMessage &pm){
    handle.name = pm.nodeinforeply().name();
    handle.id = bignum::parseStr(pm.nodeinforeply().id().c_str());
    handle.type = pm.nodeinforeply().type();
    cout << "Discovered Node Info for " << handle.ip << ":" << endl;
    cout << "\tName: " << handle.name << endl;
    cout << "\tId: " << handle.id.toStr() << endl;
    cout << "\tType: " << nodeTypeNames[handle.type]  << endl;
}

void resolver::nodePayload(socketHandle &handle, protobufMessage &pm) {
}

void resolver::share(socketHandle &handle, protobufMessage &pm) {

}


//void resolver::exampleMessage(socketHandle &handle, protobufMessage &pm) {
//    cout << handle.ip << "> " << pm.examplemessage().message() << endl;
//}
