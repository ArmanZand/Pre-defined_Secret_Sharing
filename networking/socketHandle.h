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
#include "../bignum.h"
#pragma comment(lib, "ws2_32")

using namespace std;


class socketHandle {
public:
    socketHandle();
    ~socketHandle();
    SOCKET mSocket{};
    sockaddr_in handleAddr{};
    nodeType type;
    string ip;
    string name;
    bignum id;
    fd_set descriptor{};
    unique_ptr<std::thread> connect(string remoteAddress, string remotePort);
    void send(protobufMessage & message);
    bool isConnected();
    void receive();
    bool operator==(socketHandle & other);
    bool operator==(const socketHandle & other);
    bool operator!=(socketHandle & other);
    bool operator!=(const socketHandle & other);

    void disconnect();

private:
    void connectInstance(string remoteAddress, string remotePort);
    char * m_buffer = new char[p_constBufferSize];
};

class handleTracker {
private:

public:
    static vector<socketHandle*> m_handles;
    static void add(socketHandle * handle);
    static void remove(socketHandle * handle);
    static void clear();
};

#endif //CLEAN_SOCKETS_SOCKETHANDLE_H
