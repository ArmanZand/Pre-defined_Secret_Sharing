//
// Created by arman on 27/03/2023.
//

#ifndef CLEAN_SOCKETS_BIGNUM_H
#define CLEAN_SOCKETS_BIGNUM_H
#include <gmp.h>
#include <string>

class bignum {
private:
    mpz_t value;
public:
    bignum(const char * str = "0");
    bignum(int input);
    ~bignum();
    std::string toStr();
    std::string toHex();
    int toInt();
    int bitLength();
    bignum copy();

    static bignum parseHex(const char * hex);
    static bignum parseBytes(unsigned char * bytes, size_t count);
    static bignum parseStr(const char * str);


    bignum operator-();
    bignum operator+(bignum &other);
    bignum operator+=(bignum &other);
    bignum operator-(bignum &other);
    bignum operator*(bignum &other);
    bignum operator*=(bignum &other);
    std::pair<bignum, bignum> operator/(bignum &other);
    bignum operator%(bignum &other);
    bignum operator^(unsigned long int &exponent);
    bool operator==(bignum &other);
    bool operator==(const bignum &other);
    bool operator==(int other);
    bool operator!=(bignum &other);
    bool operator<(bignum &other);
    bool operator>(bignum &other);
    bool operator<=(bignum &other);
    bool operator>=(bignum &other);
    bignum operator>>(int bitshift);
    bignum operator<<(int bitshift);
    bignum operator &(bignum &other);
    bignum operator |=(bignum &other);
    friend std::ostream & operator<<(std::ostream & out, bignum & obj){
        return out << obj.value;
    }

    static bignum modpow(bignum & base, bignum & exponent, bignum & mod);
    static bignum gcd(bignum & a, bignum & b);
    static bignum modinv(bignum & a, bignum & p);
};


#endif //CLEAN_SOCKETS_BIGNUM_H
