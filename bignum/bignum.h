//
// Created by arman on 27/03/2023.
//

#ifndef CLEAN_SOCKETS_BIGNUM_H
#define CLEAN_SOCKETS_BIGNUM_H
#include <gmp.h>
#include <string>
using namespace std;
class bignum {
private:
    mpz_t value;
public:
    bignum(const char * str = "0");

    static bignum parseBytes(unsigned char * bytes, size_t count);

    bignum operator+(bignum &other);
    bignum operator+=(bignum &other);
    bignum operator-(bignum &other);
    bignum operator*(bignum &other);
    pair<bignum, bignum> operator/(bignum &other);
    bignum operator%(bignum &other);
    bignum operator^(unsigned long int &exponent);
    bool operator==(bignum &other);
    bool operator!=(bignum &other);
    bool operator<(bignum &other);
    bool operator>(bignum &other);
    bool operator<=(bignum &other);
    bool operator>=(bignum &other);
    friend ostream & operator<<(ostream & out, bignum & obj){
        return out << obj.value;
    }

    static bignum modpow(bignum & base, bignum & exponent, bignum & mod);
    static bignum gcd(bignum & a, bignum & b);
    static bignum modinv(bignum & a, bignum & p);
};


#endif //CLEAN_SOCKETS_BIGNUM_H
