//
// Created by arman on 15/03/2023.
//

#ifndef CLEAN_SOCKETS_CRYPTOUTILITIES_H
#define CLEAN_SOCKETS_CRYPTOUTILITIES_H
#include "../bignum.h"
#include <vector>

class cryptoUtilities {
public:
    static void secureRandom(unsigned char * buffer, size_t length);
    static bignum nextBignum(bignum & min, bignum & max);
    static bignum nextBignum(int min, int max);
    static std::vector<bignum> uniqueBignumVector(int length, bignum & min, bignum & max);
};


#endif //CLEAN_SOCKETS_CRYPTOUTILITIES_H
