//
// Created by arman on 12/03/2023.
//
#include "socketHandle.h"
#include "socketEvents.h"
#include <iostream>
#include <Ws2tcpip.h>

bool keepTrying = true;
int waitRetry = 1000;
void socketHandle::connectInstance(string remoteAddress, string remotePort) {
    try {
        WSAData wsaData;
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if(iResult != 0){
            throw runtime_error("WSAStartup failed.");
        }

        this->mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(this->mSocket == INVALID_SOCKET){
            throw runtime_error("Error creating socket.");
        }

        u_long mode = 1;
        iResult = ioctlsocket(this->mSocket, FIONBIO, &mode);
        if(iResult == SOCKET_ERROR){
            throw runtime_error("Error setting socket to non-blocking mode.");
        }

        struct addrinfo* result = nullptr;
        struct addrinfo hints {};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        iResult = getaddrinfo(remoteAddress.c_str(),remotePort.c_str(), &hints, &result);
        if(iResult == SOCKET_ERROR) {
            std::cerr << "Error initiating connection: " << WSAGetLastError() << std::endl;
            closesocket(this->mSocket);
            WSACleanup();
        }

        iResult = ::connect(this->mSocket, result->ai_addr, (int)result->ai_addrlen);

        if(iResult == SOCKET_ERROR){
            int error = WSAGetLastError() ;
            if(error != WSAEWOULDBLOCK){
                std::cerr << "Error initiating connection: " << error << std::endl;
                closesocket(this->mSocket);
                WSACleanup();
            }
            else if (error == WSAECONNREFUSED){
                //WSAECONNREFUSED if peer is not listening
                //try to connect again after some time

            }
        }

        fd_set writeSet;
        FD_ZERO(&writeSet);
        FD_SET(mSocket, &writeSet);
        timeval timeout = {10, 0};
        iResult = select(0, nullptr, &writeSet, nullptr, &timeout);
        if(iResult == SOCKET_ERROR){
            throw runtime_error("Error waiting for connection.");
        }
        else if(result == 0){
            throw runtime_error("Timeout waiting for connection.");
        }

        int handleAddrLen = sizeof(handleAddr);
        getpeername(mSocket, (sockaddr*)&handleAddr, &handleAddrLen);
        ip = string(inet_ntoa(handleAddr.sin_addr)) + ":" + std::to_string(handleAddr.sin_port);
        socketEvents::getInstance().onConnected(this);
    }
    catch(const exception &ex){
        closesocket(mSocket);
        cerr << "Exception: " << ex.what() << endl;
        cerr << "WSACode: " << WSAGetLastError() << endl;
        if(keepTrying){
            closesocket(mSocket);
            WSACleanup();
            Sleep(waitRetry);
            cout << "Could not connect to " << remoteAddress << ":" << remotePort << ", retrying..." << endl;
            connectInstance(remoteAddress, remotePort);
        } else {
            cout << "Could not connect to " << remoteAddress << ":" << remotePort << ", terminating connection attempt." << endl;
        }
    }








}

void socketHandle::connect(string remoteAddress, string remotePort){
    thread connectThread([&remoteAddress, &remotePort, this]() {this->connectInstance(remoteAddress, remotePort);});
    connectThread.join();
}

socketHandle::socketHandle() {

}

