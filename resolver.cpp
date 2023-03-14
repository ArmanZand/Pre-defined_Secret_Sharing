//
// Created by arman on 14/03/2023.
//
#include <functional>
#include "resolver.h"

using commandHandler = function<void(socketHandle &, protobufMessage &)>;
unordered_map<protobufMessage::CommandCase, commandHandler> commands = {
        {protobufMessage::kExampleMessage, resolver::exampleMessage }
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


void resolver::exampleMessage(socketHandle &handle, protobufMessage &pm) {
    cout << handle.ip << "> " << pm.examplemessage().message() << endl;
}
