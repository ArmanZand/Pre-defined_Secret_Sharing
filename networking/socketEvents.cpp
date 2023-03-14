//
// Created by arman on 12/03/2023.
//
#include "socketEvents.h"
#include "socketHandle.h"
#include <algorithm>
socketEvents &socketEvents::getInstance() {
    static socketEvents instance;
    return instance;
}

void socketEvents::setOnConnected(socketEvents::handleConnectedEvent handler) {
    onConnectedHandlers.push_back(handler);
}

void socketEvents::onConnected(socketHandle *handle) {
    for(handleConnectedEvent & onConnectEvent : onConnectedHandlers){
        onConnectEvent(handle);
    }
}

void socketEvents::removeOnConnected(socketEvents::handleConnectedEvent handler){
    for (size_t i = 0; i < onConnectedHandlers.size(); i++){
        if (onConnectedHandlers[i].target_type() == handler.target_type() &&
            onConnectedHandlers[i].target<void(socketHandle*)>() == handler.target<void(socketHandle*)>()){
            onConnectedHandlers.erase(onConnectedHandlers.begin() + i);
            return;
        }
    }
}

void socketEvents::setOnDisconnected(socketEvents::handleDisconnectedEvent handler) {
    onDisconnectedHandlers.push_back(handler);
}

void socketEvents::removeOnDisconnected(socketEvents::handleDisconnectedEvent handler) {
    for (size_t i = 0; i < onDisconnectedHandlers.size(); i++){
        if (onDisconnectedHandlers[i].target_type() == handler.target_type() &&
            onDisconnectedHandlers[i].target<void(socketHandle*)>() == handler.target<void(socketHandle*)>()){
            onDisconnectedHandlers.erase(onDisconnectedHandlers.begin() + i);
            return;
        }
    }
}

void socketEvents::onDisconnected(socketHandle *handle) {
    for(handleDisconnectedEvent & onDisconnectEvent : onDisconnectedHandlers){
        onDisconnectEvent(handle);
    }
}


void socketEvents::setOnReady(socketEvents::handleReadyEvent handler) {
    onReadyHandlers.push_back(handler);
}

void socketEvents::removeOnReady(socketEvents::handleReadyEvent handler) {
    for (size_t i = 0; i < onReadyHandlers.size(); i++){
        if (onReadyHandlers[i].target_type() == handler.target_type() &&
            onReadyHandlers[i].target<void(socketHandle*)>() == handler.target<void(socketHandle*)>()){
            onReadyHandlers.erase(onReadyHandlers.begin() + i);
            return;
        }
    }
}

void socketEvents::onReady(socketHandle *handle, bool initiator) {
    for(handleReadyEvent & onReadyEvent : onReadyHandlers){
        onReadyEvent(handle, initiator);
    }
}

void socketEvents::setOnReceive(socketEvents::handleReceiveEvent handler) {
    onReceiveHandlers.push_back(handler);
}

void socketEvents::removeOnReceive(socketEvents::handleReceiveEvent handler) {
    for (size_t i = 0; i < onReceiveHandlers.size(); i++){
        if (onReceiveHandlers[i].target_type() == handler.target_type() &&
            onReceiveHandlers[i].target<void(socketHandle*, protobufMessage*)>() == handler.target<void(socketHandle*, protobufMessage*)>()){
            onReceiveHandlers.erase(onReceiveHandlers.begin() + i);
            return;
        }
    }
}

void socketEvents::onReceive(socketHandle *handle, protobufMessage * message) {
    for(handleReceiveEvent & onReceiveEvent : onReceiveHandlers){
        onReceiveEvent(handle, message);
    }
}


