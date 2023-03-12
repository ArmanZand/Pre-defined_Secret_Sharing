//
// Created by arman on 12/03/2023.
//

#ifndef CLEAN_SOCKETS_LISTENER_H
#define CLEAN_SOCKETS_LISTENER_H

#include "socketHandle.h"
#include <string>
#include <functional>
using namespace std;

class listener {
public:
    using connected = function<void(socketHandle)>;
    connected onConnected;
    void start(string localAddress, string localPort);
private:
    void listenInstance(string localAddress, string localPort);

};


#endif //CLEAN_SOCKETS_LISTENER_H
