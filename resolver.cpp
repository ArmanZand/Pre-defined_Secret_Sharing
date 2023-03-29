//
// Created by arman on 14/03/2023.
//
#include <functional>
#include "resolver.h"


using commandHandler = function<void(socketHandle *, protobufMessage &)>;
unordered_map<protobufMessage::CommandCase, commandHandler> commands = {
        { protobufMessage::kNodeInfo, resolver::nodeInfo },
        { protobufMessage::kNodeInfoReply, resolver::nodeInfoReply },
        { protobufMessage::kNodeInfoAck, resolver::nodeInfoAck },
        { protobufMessage::kNodePayload, resolver::nodePayload },

        { protobufMessage::kShare, resolver::share }
};
void resolver::execute(socketHandle *handlePtr, protobufMessage &pm) {
    try {
        auto it = commands.find(pm.command_case());
        if(it != commands.end()){
            it->second(handlePtr, pm);
        }
        else {
            throw runtime_error("Command not recognised.");
        }

    }
    catch(exception & ex){
        cerr << ex.what() << endl;
    }
}
void resolver::nodeInfo(socketHandle *handlePtr, protobufMessage &pm){
    handlePtr->name = pm.nodeinfo().name();
    handlePtr->id = bignum::parseStr(pm.nodeinfo().id().c_str());
    handlePtr->type = pm.nodeinfo().type();
    cout << "Discovered Node Info for " << handlePtr->ip << ":" << endl;
    cout << "\tName: " << handlePtr->name << endl;
    cout << "\tId: " << handlePtr->id.toStr() << endl;
    cout << "\tType: " << nodeTypeNames[handlePtr->type] << endl;
    protobufMessage rm;
    rm.mutable_nodeinforeply()->set_id(get<bignum>(config["NODE_ID"]).toStr());
    rm.mutable_nodeinforeply()->set_name(get<string>(config["NODE_NAME"]));
    rm.mutable_nodeinforeply()->set_type(static_cast<nodeType>(get<int>(config["NODE_TYPE"])));
    handlePtr->send(rm);
}

void resolver::nodeInfoReply(socketHandle *handlePtr, protobufMessage &pm){
    handlePtr->name = pm.nodeinforeply().name();
    handlePtr->id = bignum::parseStr(pm.nodeinforeply().id().c_str());
    handlePtr->type = pm.nodeinforeply().type();
    cout << "Discovered Node Info for " << handlePtr->ip << ":" << endl;
    cout << "\tName: " << handlePtr->name << endl;
    cout << "\tId: " << handlePtr->id.toStr() << endl;
    cout << "\tType: " << nodeTypeNames[handlePtr->type] << endl;
    protobufMessage rm;
    rm.mutable_nodeinfoack();
    handlePtr->send(rm);
}

void resolver::nodeInfoAck(socketHandle *handlePtr, protobufMessage &pm){

}

void resolver::nodePayload(socketHandle *handlePtr, protobufMessage &pm) {
}

void resolver::share(socketHandle *handlePtr, protobufMessage &pm) {

}


//void resolver::exampleMessage(socketHandle &handle, protobufMessage &pm) {
//    cout << handle.ip << "> " << pm.examplemessage().message() << endl;
//}
