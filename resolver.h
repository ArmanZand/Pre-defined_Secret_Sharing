//
// Created by arman on 14/03/2023.
//

#ifndef CLEAN_SOCKETS_RESOLVER_H
#define CLEAN_SOCKETS_RESOLVER_H

#include "networking/socketHandle.h"
#include "networking/networkMessage.pb.h"
#include "cryptography/polynomial.h"
class resolver {
private:
    static void secretSharerProcedure(socketHandle *handlePtr);
    static vector<bignum> playerSecrets;
    static void dealerProcedure();
    static void secretRecovererProcedure();
public:
    static void execute(socketHandle * handlePtr, protobufMessage & pm);

    static void nodeInfo(socketHandle *handlePtr, protobufMessage & pm);
    static void nodeInfoReply(socketHandle *handlePtr, protobufMessage & pm);
    static void nodeInfoAck(socketHandle *handlePtr, protobufMessage & pm);
    static void nodePayload(socketHandle *handlePtr, protobufMessage & pm);
    static void dealerShare(socketHandle *handlePtr, protobufMessage & pm);
    static void broadcastShare(socketHandle *handlePtr, protobufMessage & pm);
    static vector<point> receivedShares;
};

#endif //CLEAN_SOCKETS_RESOLVER_H
