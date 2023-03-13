//
// Created by arman on 12/03/2023.
//
#include "socketHandle.h"
#include "socketEvents.h"
#include <iostream>
#include <Ws2tcpip.h>
#include <algorithm>

#include "parameters.h"

char * m_buffer = new char [m_bufferSize];
char * message;

using namespace std;
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
        const char * data = message.c_str();

        int dataSize = message.size();
        int totalSize = dataSize +prefixSize;
        char buffer[m_bufferSize];
        memset(buffer, 0, m_bufferSize);

        ::uint32_t networkDataSize = htonl(dataSize);
        memcpy(buffer, &networkDataSize, prefixSize);

        int minToSend = min(dataSize, (int)m_bufferSize - prefixSize);
        memcpy(buffer + prefixSize, data, minToSend);

        int bytesSent = ::send(mSocket, buffer, min((int)m_bufferSize, dataSize + prefixSize), 0);
        if(bytesSent == SOCKET_ERROR){
            throw runtime_error("Error sending data.");
        } else {
            int remainingSize = totalSize - bytesSent;
            int totalSent = bytesSent - prefixSize;
            while(remainingSize > 0){
                int bytesToSend = min(remainingSize, (int)m_bufferSize);

                memcpy(buffer, data +  totalSent, bytesToSend);
                bytesSent = ::send(mSocket,  data + totalSent, bytesToSend, 0);
                if(bytesSent == SOCKET_ERROR){
                    int err = WSAGetLastError();
                    throw runtime_error("Error during the sending of multiple packets.");
                }
                remainingSize -= bytesSent;
                totalSent += bytesSent;
            }
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
                int bytesReceived = recv(mSocket, m_buffer, m_bufferSize, 0);
                if(bytesReceived == SOCKET_ERROR){
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

                } else if (bytesReceived == 0){
                    socketEvents::getInstance().onDisconnected(this);
                    break;
                } else {
                    delete[] message;

                    ::uint32_t networkDataSize;
                    memcpy(&networkDataSize, m_buffer, prefixSize);
                    int dataSize = ntohl(networkDataSize);
                    message = new char[dataSize];

                    memcpy(message, m_buffer + prefixSize, min(bytesReceived - prefixSize, dataSize));

                    int remainingSize = dataSize - bytesReceived + prefixSize;
                    int totalReceived = bytesReceived - prefixSize;
                    while(remainingSize > 0){
                        int bytesReceived = ::recv(mSocket, m_buffer, min((int)m_bufferSize, remainingSize),0);
                        if(bytesReceived == SOCKET_ERROR){
                            int wsa_error = WSAGetLastError();
                            if(wsa_error == WSAEWOULDBLOCK){
                                Sleep(10);
                                continue;
                            }
                            else {
                                throw runtime_error("Error occurred during receiving of multiple packets.");
                            }
                        }
                        memcpy(message + totalReceived, m_buffer, bytesReceived);
                        remainingSize -= bytesReceived;
                        totalReceived += bytesReceived;
                    }
                    string result(message, dataSize);
                    delete[] message;
                    socketEvents::getInstance().onReceive(this, result);
                }
            }
        }
        catch (exception &ex){
            cerr << ex.what() << endl;
            //cerr << "WSACode: " << WSAGetLastError() << endl;
            delete[] message;
            socketEvents::getInstance().onDisconnected(this);
            closesocket(mSocket);
            WSACleanup();
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
            socketEvents::getInstance().onReady(this, true);
            receive();
        }
    }
    catch(const exception &ex){
        closesocket(mSocket);
        WSACleanup();
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

