//
// Created by arman on 15/03/2023.
//

#include "cryptoUtilities.h"
#include <Windows.h>
#include <bcrypt.h>
#include <iostream>


void cryptoUtilities::secureRandom(unsigned char * buffer, size_t length) {
    BCRYPT_ALG_HANDLE hProvider;
    BCryptOpenAlgorithmProvider(&hProvider, BCRYPT_RNG_ALGORITHM, NULL, 0);
    BCryptGenRandom(hProvider, buffer, length, 0);
    BCryptCloseAlgorithmProvider(hProvider, 0);
}


bignum cryptoUtilities::nextBignum(int min, int max) {
    bignum _min(min);
    bignum _max(max);
    return nextBignum(_min, _max);
}



bignum cryptoUtilities::nextBignum(bignum &min, bignum &max) {
    if(min == max) return min;
    if(min > max)
        throw std::invalid_argument("nextBignum(): min is greater than max");

    bignum range = max - min;
    if(range == 0) return min;

    bignum mask = range.copy();
    int numSize = range.bitLength() / 8 + 1;
    int iter = (int)log2(numSize * 8);
    for(int i = 0; i < iter; i++){
        int bitshift = pow(2, i);
        bignum shifted_num = mask >> bitshift;
        mask |= shifted_num;
    }
    bignum result(0);
    unsigned char * r_bytes = new unsigned char [numSize];
    do {
        cryptoUtilities::secureRandom(r_bytes, numSize);
        bignum random_num = bignum::parseBytes(r_bytes, numSize);
        result = random_num & mask;
    }
    while( result > range);
    result += min;
    delete[] r_bytes;
    return result;
}

std::vector <bignum> cryptoUtilities::uniqueBignumVector(int length, bignum &min, bignum &max) {
    std::vector<bignum> result;
    while(result.size() < length) {
        bignum next = cryptoUtilities::nextBignum(min, max);
        if(std::find(result.begin(), result.end(), next) == result.end()){
            result.push_back(next);
        }
    }
    return result;
}
