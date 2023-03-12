//
// Created by arman on 12/03/2023.
//

#ifndef CLEAN_SOCKETS_SOCKETHANDLE_H
#define CLEAN_SOCKETS_SOCKETHANDLE_H

#include <string>
#include <WinSock2.h>
#include <thread>
#include "socketEvents.h"
#pragma comment(lib, "ws2_32")

using namespace std;
class socketHandle : public socketEvents {
public:
    SOCKET mSocket;
    sockaddr_in handleAddr;
    string ip;

    void connect(string remoteAddress, string remotePort);
private:
    void connectInstance(string remoteAddress, string remotePort);
};


#endif //CLEAN_SOCKETS_SOCKETHANDLE_H
