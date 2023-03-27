//
// Created by arman on 15/03/2023.
//

#include "cryptoUtilities.h"
#include <Windows.h>
#include <bcrypt.h>


void cryptoUtilities::secureRandom(unsigned char * buffer, size_t length) {
    BCRYPT_ALG_HANDLE hProvider;
    BCryptOpenAlgorithmProvider(&hProvider, BCRYPT_RNG_ALGORITHM, NULL, 0);
    BCryptGenRandom(hProvider, buffer, length, 0);
    BCryptCloseAlgorithmProvider(hProvider, 0);
}
