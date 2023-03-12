//
// Created by arman on 12/03/2023.
//
#include "socketEvents.h"
#include "socketHandle.h"

void socketEvents::setOnConnected(socketEvents::handleConnectedEvent handler) {
    onConnectedHandlers.push_back(handler);
}
template<typename T>
void socketEvents::removeEvent(vector<T> & handlers, const T& handler){
    for(size_t i = 0; i < handlers.size(); i++){
        if (handlers[i].target_type() == handler.target_type() &&
            handlers[i].template target<void(T)>() == handler.template target<void(T)>()) {
            handlers.erase(handlers.begin() + i);
            return;
        }
    }
}
void socketEvents::removeOnConnected(socketEvents::handleConnectedEvent handler){
    removeEvent(onConnectedHandlers, handler);
    /*
    for (size_t i = 0; i < onConnectedHandlers.size(); i++){
        if (onConnectedHandlers[i].target_type() == handler.target_type() &&
            onConnectedHandlers[i].target<void(socketHandle*)>() == handler.target<void(socketHandle*)>()){
            onConnectedHandlers.erase(onConnectedHandlers.begin() + i);
            return;
        }
    }*/
}

void socketEvents::setOnDisconnected(socketEvents::handleDisconnectedEvent handler) {
    onDisconnectedHandlers.push_back(handler);
}

void socketEvents::removeOnDisconnected(socketEvents::handleDisconnectedEvent handler) {
    removeEvent(onDisconnectedHandlers, handler);
}



void socketEvents::onConnected(socketHandle *handle) {
    for(handleConnectedEvent & onConnectEvent : onConnectedHandlers){
        onConnectEvent(handle);
    }
}

void socketEvents::onDisconnected(socketHandle *handle) {
    for(handleDisconnectedEvent & onDisconnectEvent : onDisconnectedHandlers){
        onDisconnectEvent(handle);
    }
}

socketEvents &socketEvents::getInstance() {
    static socketEvents instance;
    return instance;
}


