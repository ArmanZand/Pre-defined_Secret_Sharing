//
// Created by arman on 12/03/2023.
//

#ifndef CLEAN_SOCKETS_SOCKETHANDLE_H
#define CLEAN_SOCKETS_SOCKETHANDLE_H

#include <string>
#include <WinSock2.h>
#include <thread>
#include "socketEvents.h"
#include "networkMessage.pb.h"
#include "../parameters.h"
#pragma comment(lib, "ws2_32")

using namespace std;
class socketHandle {
public:
    socketHandle();
    ~socketHandle();
    SOCKET mSocket{};
    sockaddr_in handleAddr{};
    string ip;
    fd_set descriptor{};
    void connect(string remoteAddress, string remotePort);
    void send(protobufMessage & message);
    bool isConnected();
    void receive();

private:
    void connectInstance(string remoteAddress, string remotePort);
    char * m_buffer = new char[p_constBufferSize];
};


#endif //CLEAN_SOCKETS_SOCKETHANDLE_H
