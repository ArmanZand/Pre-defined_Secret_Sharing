//
// Created by arman on 13/03/2023.
//

#ifndef CLEAN_SOCKETS_PARAMETERS_H
#define CLEAN_SOCKETS_PARAMETERS_H


constexpr int m_bufferSize = 8192;
bool keepTrying = true;
int waitRetry = 1000;
const int prefixSize = sizeof(int);

//TODO:
//1. correct destruction
//2. config file
//3. listener status events
//4. protobuf
//5. scripting

#endif //CLEAN_SOCKETS_PARAMETERS_H
