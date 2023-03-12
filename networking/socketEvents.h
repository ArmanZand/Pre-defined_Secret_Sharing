//
// Created by arman on 12/03/2023.
//
#pragma once
#ifndef CLEAN_SOCKETS_SOCKETEVENTS_H
#define CLEAN_SOCKETS_SOCKETEVENTS_H

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

    void setOnConnected(handleConnectedEvent handler);
    void removeOnConnected(handleConnectedEvent handler);

    void setOnDisconnected(handleDisconnectedEvent handler);
    void removeOnDisconnected(handleDisconnectedEvent handler);

    void onConnected(socketHandle * handle);
    void onDisconnected(socketHandle * handle);
private:
    handleConnectedEvent onConnected_;
    handleDisconnectedEvent onDisconnected_;
    vector<handleConnectedEvent> onConnectedHandlers;
    vector<handleDisconnectedEvent> onDisconnectedHandlers;
    template<typename T>
    void removeEvent(vector<T> &handlers, const T &handler);
};



#endif //CLEAN_SOCKETS_SOCKETEVENTS_H
