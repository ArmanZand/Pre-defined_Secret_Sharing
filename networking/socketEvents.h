//
// Created by arman on 12/03/2023.
//
#pragma once
#ifndef CLEAN_SOCKETS_SOCKETEVENTS_H
#define CLEAN_SOCKETS_SOCKETEVENTS_H

#include "networkMessage.pb.h"
#include "socketHandle.h"
#include <functional>
#include <vector>

using namespace std;

class socketHandle;

class socketEvents {
public:

    static socketEvents& getInstance();

    using handleConnectedEvent = function<void(socketHandle *)>;
    using handleDisconnectedEvent = function<void(socketHandle *)>;
    using handleReadyEvent = function<void(socketHandle *, bool)>;
    using handleReceiveEvent = function<void(socketHandle *, protobufMessage *)>;

    void setOnConnected(handleConnectedEvent handler);
    void removeOnConnected(handleConnectedEvent handler);

    void setOnDisconnected(handleDisconnectedEvent handler);
    void removeOnDisconnected(handleDisconnectedEvent handler);

    void setOnReady(handleReadyEvent handler);
    void removeOnReady(handleReadyEvent handler);

    void setOnReceive(handleReceiveEvent handler);
    void removeOnReceive(handleReceiveEvent handler);

    void onConnected(socketHandle * handle);
    void onDisconnected(socketHandle * handle);
    void onReady(socketHandle * handle, bool initiator);
    void onReceive(socketHandle * handle, protobufMessage * message);
private:
    vector<handleConnectedEvent> onConnectedHandlers;
    vector<handleDisconnectedEvent> onDisconnectedHandlers;
    vector<handleReadyEvent> onReadyHandlers;
    vector<handleReceiveEvent> onReceiveHandlers;
};



#endif //CLEAN_SOCKETS_SOCKETEVENTS_H
