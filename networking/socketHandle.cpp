//
// Created by arman on 12/03/2023.
//
#include "socketHandle.h"
#include "socketEvents.h"
#include <iostream>
#include <Ws2tcpip.h>


static const volatile int m_bufferSize = 8192;
char * m_buffer = new char [m_bufferSize];
bool keepTrying = true;
int waitRetry = 1000;


bool socketHandle::isConnected(){
    fd_set fdCheck;
    FD_ZERO(&fdCheck);
    FD_SET(mSocket, &fdCheck);
    timeval timeout = { 0, 0 };
    int result = select(0, &fdCheck, nullptr, nullptr, &timeout);
    if (result == SOCKET_ERROR)
    {
        return false;
    }
    return (result >= 0);
}
void socketHandle::send(string message){
    try {
        if(!isConnected()){
            socketEvents::getInstance().onDisconnected(this);
            return;
        }
        const char* data = message.c_str();
        int dataLen = strlen(data);
        memcpy(m_buffer, data, dataLen);
        int result = ::send(mSocket, data, strlen(data), 0);
        if(result == SOCKET_ERROR){
            throw runtime_error("Error sending data.");
        } else {
            //Data sent.
        }
    }
    catch (exception &ex){
        cerr << ex.what() << endl;
        cerr << "WSACode: " << WSAGetLastError() << endl;
    }
}

void socketHandle::receive(){
    while(true) {
        try {
            if(!isConnected()){
                socketEvents::getInstance().onDisconnected(this);
                return;
            }
            int isReady = select(0, &descriptor, NULL, NULL, NULL);
            if(isReady == SOCKET_ERROR){
                throw runtime_error("Error waiting for data.");
            }
            else {
                int result = recv(mSocket, m_buffer, m_bufferSize, 0);
                if(result == SOCKET_ERROR){
                    int error = WSAGetLastError() ;
                    if(error == WSAEWOULDBLOCK){
                        Sleep(10);
                    }
                    else if (error == WSAECONNRESET){
                        throw runtime_error("Error on data receive, connection reset.");
                    }
                    else if (error == WSAECONNABORTED){
                        throw runtime_error("Error on data receive, connection aborted.");
                    }
                    else {
                        throw runtime_error("Error on data receive.");
                    }

                } else if (result == 0){
                    socketEvents::getInstance().onDisconnected(this);
                    break;
                } else {
                    m_buffer[result] = '\0';
                    std::string msg(m_buffer, result);
                    std::cout << "Received data: " << msg << std::endl;
                }
            }
        }
        catch (exception &ex){
            cerr << ex.what() << endl;
            //cerr << "WSACode: " << WSAGetLastError() << endl;
            socketEvents::getInstance().onDisconnected(this);
            break;
        }
    }
}
void socketHandle::connectInstance(string remoteAddress, string remotePort) {
    try {
        WSAData wsaData;
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if(iResult != 0){
            throw runtime_error("WSAStartup failed.");
        }

        mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(mSocket == INVALID_SOCKET){
            throw runtime_error("Error creating socket.");
        }

        u_long mode = 1;
        iResult = ioctlsocket(mSocket, FIONBIO, &mode);
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
            throw runtime_error("Error getting address info.");
        }

        iResult = ::connect(mSocket, result->ai_addr, (int)result->ai_addrlen);

        if(iResult == SOCKET_ERROR){
            int error = WSAGetLastError() ;
            if(error == WSAEWOULDBLOCK){
                FD_ZERO(&descriptor);
                FD_SET(mSocket, &descriptor);
                timeval timeout = {10, 0};
                iResult = select(0, nullptr, &descriptor, nullptr, &timeout);
                if(iResult == SOCKET_ERROR){
                    throw runtime_error("Error while waiting for connection to finalise.");
                }
                else if(iResult == 0){
                    throw runtime_error("Error connection attempt took too long.");
                }

            }
            else if (error == WSAECONNREFUSED){

                //WSAECONNREFUSED if peer is not listening
                //try to connect again after some time
            }
        }

        FD_ZERO(&descriptor);
        FD_SET(mSocket, &descriptor);
        timeval timeout = {10, 0};
        iResult = select(0, nullptr, &descriptor, nullptr, &timeout);
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

        if(FD_ISSET(mSocket, &descriptor)){
            receive();
        }
    }
    catch(const exception &ex){
        closesocket(mSocket);
        cerr << "Exception: " << ex.what() << endl;
        //cerr << "WSACode: " << WSAGetLastError() << endl;

    }
    if(keepTrying){
        closesocket(mSocket);
        WSACleanup();
        delete[] m_buffer;
        m_buffer = nullptr;
        m_buffer = new char[m_bufferSize];
        Sleep(waitRetry);
        cout << "Could not connect to " << remoteAddress << ":" << remotePort << ", retrying..." << endl;
        connectInstance(remoteAddress, remotePort);
    } else {
        cout << "Could not connect to " << remoteAddress << ":" << remotePort << ", terminating connection attempt." << endl;
    }
}

void socketHandle::connect(string remoteAddress, string remotePort){
    thread connectThread([&remoteAddress, &remotePort, this]() {this->connectInstance(remoteAddress, remotePort);});
    connectThread.join();
}

socketHandle::socketHandle() {

}

