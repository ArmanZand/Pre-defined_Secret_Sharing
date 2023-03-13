//
// Created by arman on 12/03/2023.
//

#include "listener.h"
//#define _WIN32_WINNT 0x0600
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>



void listener::listenInstance(string localAddress, string localPort){
    SOCKET listenSocket;
    try {
        WSAData wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if(result != 0){
            throw runtime_error("WSAStartup failed.");
        }
        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(listenSocket == INVALID_SOCKET){
            throw runtime_error("Error invalid socket.");
        }
        struct addrinfo* pAddrinfo = nullptr, * ptr = nullptr, hints;
        SecureZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        result = getaddrinfo(localAddress.c_str(), localPort.c_str(), &hints, &pAddrinfo);
        if(result != 0){
            throw runtime_error("Error getting address info.");
        }

        result = bind(listenSocket, pAddrinfo->ai_addr, (int)pAddrinfo-> ai_addrlen);
        if(result == SOCKET_ERROR){
            freeaddrinfo(pAddrinfo);
            throw runtime_error("Error binding socket.");
        }
        freeaddrinfo(pAddrinfo);
        result = listen(listenSocket, 20);
        if (result == SOCKET_ERROR) {
            throw runtime_error("Error on socket listen.");
        }
        cout << "Listen thread started on (" << localAddress << ":" << localPort << ")" << endl;

        socketHandle socketHandle;
        int handleAddrSize = sizeof(socketHandle.handleAddr);

        while(true){
            socketHandle.mSocket = accept(listenSocket, (sockaddr * ) &socketHandle.handleAddr, &handleAddrSize);
            if (socketHandle.mSocket == INVALID_SOCKET) {
                throw runtime_error("Error on socket accept.");
            }

            socketHandle.ip = std::string(inet_ntoa(socketHandle.handleAddr.sin_addr)) + ":" + std::to_string(socketHandle.handleAddr.sin_port);
            socketEvents::getInstance().onConnected(&socketHandle);

            FD_ZERO(&socketHandle.descriptor);
            FD_SET(socketHandle.mSocket, &socketHandle.descriptor);

            if(FD_ISSET(socketHandle.mSocket, &socketHandle.descriptor)){
                thread receiveThread(&socketHandle::receive, socketHandle);
                receiveThread.join();
            }
        }
    }
    catch(const exception &ex){
        closesocket(listenSocket);
        WSACleanup();
        cerr << "Exception: " << ex.what() << endl;
        //cerr << "WSACode: " << WSAGetLastError() << endl;
    }
}

void listener::start(string localAddress, string localPort){
    thread listenThread([&localAddress, &localPort, this]() { this->listenInstance(localAddress, localPort);});
    listenThread.join();
}

