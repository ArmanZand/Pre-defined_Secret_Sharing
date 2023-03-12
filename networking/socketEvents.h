//
// Created by arman on 12/03/2023.
//

#ifndef CLEAN_SOCKETS_SOCKETEVENTS_H
#define CLEAN_SOCKETS_SOCKETEVENTS_H
#pragma once
#include "socketHandle.h"
#include <functional>
#include <vector>

using namespace std;
class socketHandle;

class socketEvents {
public:
    using handleConnectedEvent = function<void(socketHandle *)>;

    void setOnConnected(handleConnectedEvent handler);
    void removeOnConnected(handleConnectedEvent handler);

protected:
    void onConnected(socketHandle * handle);

private:
    handleConnectedEvent onConnected_;
    vector<handleConnectedEvent> onConnectedHandlers;

};

void socketEvents::setOnConnected(socketEvents::handleConnectedEvent handler) {
    onConnected_ = handler;
    onConnectedHandlers.push_back(handler);
}
void socketEvents::removeOnConnected(socketEvents::handleConnectedEvent handler){
    for (size_t i = 0; i < onConnectedHandlers.size(); i++){
        if(onConnectedHandlers[i].target_type() == handler.target_type() &&
          onConnectedHandlers[i].target<void(socketHandle*)>() == handler.target<void(socketHandle*)>()){
            onConnectedHandlers.erase(onConnectedHandlers.begin() + i);
            return;
        }
    }
}

void socketEvents::onConnected(socketHandle *handle) {
    for(handleConnectedEvent & onConnectEvent : onConnectedHandlers){
        onConnectEvent(handle);
    }
}


#endif //CLEAN_SOCKETS_SOCKETEVENTS_H
