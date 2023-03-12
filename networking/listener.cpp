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

    WSAData wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != 0){
        cerr << "WSAStartup failed with error: " << result << endl;
    }
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenSocket == INVALID_SOCKET){
        cerr << "Socket failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
    }
    struct addrinfo* pAddrinfo = nullptr, * ptr = nullptr, hints;
    SecureZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(localAddress.c_str(), localPort.c_str(), &hints, &pAddrinfo);
    if(result != 0){
        cerr << "getaddrinfo failed with error: " << result << endl;
        closesocket(listenSocket);
        WSACleanup();
    }

    result = bind(listenSocket, pAddrinfo->ai_addr, (int)pAddrinfo-> ai_addrlen);
    if(result == SOCKET_ERROR){
        cerr << "bind failed with error: " << WSAGetLastError() << endl;
        freeaddrinfo(pAddrinfo);
        closesocket(listenSocket);
        WSACleanup();
    }
    freeaddrinfo(pAddrinfo);
    result = listen(listenSocket, 20);
    if (result == SOCKET_ERROR) {
        cerr << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
    }
    cout << "Listen thread started on (" << localAddress << ":" << localPort << ")" << endl;

    socketHandle socketHandle;
    int handleAddrSize = sizeof(socketHandle.handleAddr);

    while(1){
        socketHandle.mSocket = accept(listenSocket, (sockaddr * ) &socketHandle.handleAddr, &handleAddrSize);
        if (socketHandle.mSocket == INVALID_SOCKET) {
            cerr << "accept failed with error: " << WSAGetLastError() << endl;
            closesocket(listenSocket);
            WSACleanup();
        }
        //Connected;
        socketHandle.ip = std::string(inet_ntoa(socketHandle.handleAddr.sin_addr)) + ":" + std::to_string(socketHandle.handleAddr.sin_port);
    }
}

void listener::start(string localAddress, string localPort){
    thread listenThread([&localAddress, &localPort, this]() { this->listenInstance(localAddress, localPort);});
    listenThread.join();
}

