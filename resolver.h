//
// Created by arman on 14/03/2023.
//

#ifndef CLEAN_SOCKETS_RESOLVER_H
#define CLEAN_SOCKETS_RESOLVER_H

#include "networking/socketHandle.h"
#include "networking/networkMessage.pb.h"
class resolver {
public:
    static void execute(socketHandle & handle, protobufMessage & pm);

    static void exampleMessage(socketHandle & handle, protobufMessage & pm);
};

#endif //CLEAN_SOCKETS_RESOLVER_H
