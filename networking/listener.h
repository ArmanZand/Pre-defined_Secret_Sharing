//
// Created by arman on 12/03/2023.
//

#ifndef CLEAN_SOCKETS_LISTENER_H
#define CLEAN_SOCKETS_LISTENER_H

#include "socketHandle.h"
#include "socketEvents.h"
#include <string>

using namespace std;


class listener {
public:
    void start(string localAddress, string localPort);
    socketEvents events;
private:
    void listenInstance(string localAddress, string localPort);
    void connectionReady(socketHandle handle);
};


#endif //CLEAN_SOCKETS_LISTENER_H
