//
// Created by arman on 12/03/2023.
//
#include "socketEvents.h"
#include "socketHandle.h"

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

socketEvents &socketEvents::getInstance() {
    static socketEvents instance;
    return instance;
}
