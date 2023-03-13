//
// Created by arman on 13/03/2023.
//

#ifndef CLEAN_SOCKETS_PARAMETERS_H
#define CLEAN_SOCKETS_PARAMETERS_H


static const volatile int m_bufferSize = 8192;
bool keepTrying = true;
int waitRetry = 1000;
const int prefixSize = sizeof(int);

//TODO:
//1. listener status events
//2. correct destruction
//3. protobuf

#endif //CLEAN_SOCKETS_PARAMETERS_H
