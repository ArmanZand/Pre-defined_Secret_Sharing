//
// Created by arman on 12/03/2023.
//

#include "listener.h"
#define _WIN32_WINNT 0x0600
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>

#include <thread>
#pragma comment(lib, "Ws2_32.lib")

void listener::listenInstance(string localAddress, string localPort){
    cout << "Listen thread started on (" << localAddress << ":" << localPort << ")" << endl;
}

void listener::start(string localAddress, string localPort){
    thread listenThread([&localAddress, &localPort, this]() { this->listenInstance(localAddress, localPort);});
    listenThread.join();
}

