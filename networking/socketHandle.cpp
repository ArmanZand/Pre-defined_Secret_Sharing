//
// Created by arman on 12/03/2023.
//
#include "socketHandle.h"
#include "socketEvents.h"
#include <iostream>
#include <Ws2tcpip.h>
#include <algorithm>

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

void socketHandle::send(protobufMessage & message){
    try {
        if(!isConnected()){
            socketEvents::getInstance().onDisconnected(this);
            return;
        }
        int dataSize = message.ByteSizeLong();
        char * data = new char[dataSize];
        message.SerializeToArray(data, dataSize);
        int prefixSize = p_constPrefixSize;
        int totalSize = dataSize + prefixSize;
        char buffer[p_constBufferSize];
        memset(buffer, 0, p_constBufferSize);

        ::uint32_t networkDataSize = htonl(dataSize);
        memcpy(buffer, &networkDataSize, prefixSize);

        int minToSend = min(dataSize, (int)p_constBufferSize - prefixSize);
        memcpy(buffer + prefixSize, data, minToSend);

        int bytesSent = ::send(mSocket, buffer, min((int)p_constBufferSize, dataSize + prefixSize), 0);
        if(bytesSent == SOCKET_ERROR){
            throw runtime_error("Error sending data.");
        } else {
            int remainingSize = totalSize - bytesSent;
            int totalSent = bytesSent - prefixSize;
            while(remainingSize > 0){
                int bytesToSend = min(remainingSize, (int)p_constBufferSize);

                memcpy(buffer, data +  totalSent, bytesToSend);
                bytesSent = ::send(mSocket,  data + totalSent, bytesToSend, 0);
                if(bytesSent == SOCKET_ERROR){
                    int err = WSAGetLastError();
                    delete[] data;
                    throw runtime_error("Error during the sending of multiple packets.");
                }
                remainingSize -= bytesSent;
                totalSent += bytesSent;
            }
        }
        delete[] data;
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

                int bytesReceived = recv(mSocket, m_buffer, p_constBufferSize, 0);

                if(bytesReceived == SOCKET_ERROR){
                    int error = WSAGetLastError() ;
                    if(error == WSAEWOULDBLOCK){
                        continue;
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
                    ::uint32_t networkDataSize;
                    int prefixSize = p_constPrefixSize;
                    memcpy(&networkDataSize, m_buffer, prefixSize);
                    int dataSize = ntohl(networkDataSize);
                    char * message = new char[dataSize];

                    memcpy(message, m_buffer + prefixSize, min(bytesReceived - prefixSize, dataSize));

                    int remainingSize = dataSize - bytesReceived + prefixSize;
                    int totalReceived = bytesReceived - prefixSize;
                    while(remainingSize > 0){
                        int bytesReceived = ::recv(mSocket, m_buffer, min((int)p_constBufferSize, remainingSize), 0);
                        if(bytesReceived == SOCKET_ERROR){
                            int wsa_error = WSAGetLastError();
                            if(wsa_error == WSAEWOULDBLOCK){
                                continue;
                            }
                            else {
                                delete[] message;
                                throw runtime_error("Error occurred during receiving of multiple packets.");
                            }
                        }
                        memcpy(message + totalReceived, m_buffer, bytesReceived);
                        remainingSize -= bytesReceived;
                        totalReceived += bytesReceived;
                    }
                    protobufMessage pm;
                    pm.ParseFromArray(message, dataSize);

                    delete[] message;
                    socketEvents::getInstance().onReceive(this, &pm);
                }
            }
            memset(m_buffer, 0, sizeof(p_constBufferSize));
        }
        catch (exception &ex){
            cerr << ex.what() << endl;
            //cerr << "WSACode: " << WSAGetLastError() << endl;
            socketEvents::getInstance().onDisconnected(this);
            closesocket(mSocket);
            WSACleanup();
            break;
        }
    }
}
void socketHandle::connectInstance(string remoteAddress, string remotePort) {
    bool connected = false;
    do {
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
                throw runtime_error("Error getting address info.");
            }

            iResult = ::connect(this->mSocket, result->ai_addr, (int)result->ai_addrlen);

            if(iResult == SOCKET_ERROR){
                int error = WSAGetLastError() ;
                if(error == WSAEWOULDBLOCK){
                    FD_ZERO(&this->descriptor);
                    FD_SET(this->mSocket, &this->descriptor);
                    timeval timeout = {10, 0};
                    iResult = select(0, nullptr, &this->descriptor, nullptr, &timeout);
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

            FD_ZERO(&this->descriptor);
            FD_SET(this->mSocket, &this->descriptor);
            timeval timeout = {10, 0};
            iResult = select(0, nullptr, &this->descriptor, nullptr, &timeout);
            if(iResult == SOCKET_ERROR){
                throw runtime_error("Error waiting for connection.");
            }
            else if(result == 0){
                throw runtime_error("Timeout waiting for connection.");
            }

            int handleAddrLen = sizeof(this->handleAddr);
            getpeername(this->mSocket, (sockaddr*)&this->handleAddr, &handleAddrLen);
            char ipStr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(this->handleAddr.sin_addr), ipStr, INET_ADDRSTRLEN);
            this->ip = string(ipStr) + ":" + to_string(ntohs(this->handleAddr.sin_port));

            socketEvents::getInstance().onConnected(this);

            if(FD_ISSET(this->mSocket, &this->descriptor)){
                socketEvents::getInstance().onReady(this, true);
                this->receive();
            }
        }
        catch(const exception &ex){
            cerr << "Exception: " << ex.what() << endl;
            //cerr << "WSACode: " << WSAGetLastError() << endl;
        }
        closesocket(this->mSocket);
        memset(&this->handleAddr, 0, sizeof(handleAddr));

        if(get<bool>(config["KEEP_TRYING"])){
            Sleep(get<int>(config["WAIT_RETRY"]));
            cout << "Could not connect to " << remoteAddress << ":" << remotePort << ", retrying..." << endl;
        } else {
            cout << "Could not connect to " << remoteAddress << ":" << remotePort << ", terminating connection attempt." << endl;
        }
    } while (!connected && get<bool>(config["KEEP_TRYING"]));
    WSACleanup();
}

unique_ptr<std::thread> socketHandle::connect(string remoteAddress, string remotePort){
    return make_unique<thread>([remoteAddress, remotePort, this]() { this->connectInstance(remoteAddress, remotePort);});
}

void socketHandle::disconnect() {
    closesocket(mSocket);
    WSACleanup();
}

socketHandle::socketHandle() {

}

socketHandle::~socketHandle() {

}

bool socketHandle::operator==(socketHandle &other) {
     return (this->id == other.id && this->name == other.name && this->ip == other.ip);

}

bool socketHandle::operator!=(socketHandle &other) {
    return !(*this == other);
}

bool socketHandle::operator==(const socketHandle &other) {
    return (this->id == other.id && this->name == other.name && this->ip == other.ip);
}



bool socketHandle::operator!=(const socketHandle &other) {
    return !(*this == other);
}


vector<socketHandle*> handleTracker::m_handles;
void handleTracker::add(socketHandle * handle) {
    for (auto iter = m_handles.begin(); iter != m_handles.end(); ++iter){
        if(*iter == handle){
            return;
        }
    }
    m_handles.push_back(handle);
}

void handleTracker::remove(socketHandle * handle) {
    for(auto iter = m_handles.begin(); iter != m_handles.end(); ++iter){
        if(*iter == handle){
            swap(*iter, m_handles.back());
            m_handles.pop_back();
            return;
        }
    }
}

