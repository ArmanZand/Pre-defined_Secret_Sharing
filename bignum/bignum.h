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

    bignum operator+(const bignum &other);
    bignum operator-(const bignum &other);
    bignum operator*(const bignum &other);
    pair<bignum, bignum> operator/(const bignum &other);
    bignum operator%(const bignum &other);
    bignum operator^(unsigned long int &exponent);
    bool operator==(const bignum &other);
    bool operator!=(const bignum &other);
    bool operator<(const bignum &other);
    bool operator>(const bignum &other);
    bool operator<=(const bignum &other);
    bool operator>=(const bignum &other);
    friend ostream & operator<<(ostream & out, const bignum & obj){
        return out << obj.value;
    }

    static bignum modpow(const bignum & base, const bignum & exponent, const bignum & mod);
    static bignum gcd(const bignum & a, const bignum & b);
    static bignum modinv(const bignum & a, const bignum & p);

};


#endif //CLEAN_SOCKETS_BIGNUM_H
