//
// Created by arman on 14/03/2023.
//

#ifndef CLEAN_SOCKETS_RESOLVER_H
#define CLEAN_SOCKETS_RESOLVER_H

#include "networking/socketHandle.h"
#include "networking/networkMessage.pb.h"

class resolver {
public:
    static void execute(socketHandle * handlePtr, protobufMessage & pm);

    static void nodeInfo(socketHandle *handlePtr, protobufMessage & pm);
    static void nodeInfoReply(socketHandle *handlePtr, protobufMessage & pm);
    static void nodeInfoAck(socketHandle *handlePtr, protobufMessage & pm);
    static void nodePayload(socketHandle *handlePtr, protobufMessage & pm);
    static void share(socketHandle *handlePtr, protobufMessage & pm);

};

#endif //CLEAN_SOCKETS_RESOLVER_H
