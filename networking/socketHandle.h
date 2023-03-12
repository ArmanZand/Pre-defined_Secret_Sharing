//
// Created by arman on 12/03/2023.
//

#ifndef CLEAN_SOCKETS_SOCKETHANDLE_H
#define CLEAN_SOCKETS_SOCKETHANDLE_H

#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

using namespace std;
class socketHandle {
public:
    SOCKET mSocket;
    sockaddr_in handleAddr;
    string ip;
};


#endif //CLEAN_SOCKETS_SOCKETHANDLE_H
