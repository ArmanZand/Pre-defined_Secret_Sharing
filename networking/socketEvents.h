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

    void setOnConnected(handleConnectedEvent handler);
    void removeOnConnected(handleConnectedEvent handler);

    void onConnected(socketHandle * handle);

private:
    handleConnectedEvent onConnected_;
    vector<handleConnectedEvent> onConnectedHandlers;

};



#endif //CLEAN_SOCKETS_SOCKETEVENTS_H
