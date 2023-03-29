//
// Created by arman on 12/03/2023.
//

#include "listener.h"
//#define _WIN32_WINNT 0x0600
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>

using namespace std;
void listener::connectionReady(socketHandle * handlePtr){
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(handlePtr->handleAddr.sin_addr), ipStr, INET_ADDRSTRLEN);
    handlePtr->ip = string(ipStr) + ":" + to_string(ntohs(handlePtr->handleAddr.sin_port));
    socketEvents::getInstance().onConnected(handlePtr);

    FD_ZERO(&(handlePtr->descriptor));
    FD_SET(handlePtr->mSocket, &(handlePtr->descriptor));

    if(FD_ISSET(handlePtr->mSocket, &handlePtr->descriptor)){
        socketEvents::getInstance().onReady(handlePtr, false);
        handlePtr->receive();
    }
}

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

        result = ::bind(listenSocket, pAddrinfo->ai_addr, (int)pAddrinfo-> ai_addrlen);
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

        while(true){
            SOCKET temp_socket;
            sockaddr_in temp_handleAddr {};
            //
            int handleAddrSize = sizeof(temp_handleAddr);
            temp_socket = ::accept(listenSocket, (sockaddr * ) &(temp_handleAddr), &handleAddrSize);
            if (temp_socket == INVALID_SOCKET) {
                int wsa_error = WSAGetLastError();
                if(wsa_error == WSAEINTR){
                    listenInstance(localAddress, localPort);
                }
                runtime_error("Error on socket accept: " + to_string(wsa_error));
            }
            socketHandle * handlePtr = new socketHandle();
            handlePtr->mSocket = temp_socket;
            handlePtr->handleAddr = temp_handleAddr;
            if(handlePtr->isConnected()){
                make_unique<thread>([handlePtr, this]() {this->connectionReady(handlePtr);})->detach();
            }
        }
    }
    catch(const exception &ex){
        closesocket(listenSocket);
        WSACleanup();
        cerr << ex.what() << endl;
        //cerr << "WSACode: " << WSAGetLastError() << endl;
    }
}

unique_ptr<thread> listener::start(string localAddress, string localPort){
    return make_unique<thread>([localAddress, localPort, this]() { this->listenInstance(localAddress, localPort); });
}

