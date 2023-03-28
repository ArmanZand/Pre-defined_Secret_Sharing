//
// Created by arman on 27/03/2023.
//

#include "bignum.h"
#include <iostream>

bignum::~bignum() {
    //mpz_clear(value);
}


bignum::bignum(const char * str) {
    int flag = mpz_init_set_str(value, str, 10);
    if(flag == -1){
        throw runtime_error("bignum parsing: Input base is not correct.");
        mpz_clear(value);
    }

}

bignum::bignum(int input) {
    //int flag = mpz_init_set_str(value, str, 10);
    mpz_init_set_ui(value, input);
}

bignum bignum::operator+(bignum &other) {
    bignum result;
    mpz_add(result.value, value, other.value);
    return result;
}

bignum bignum::operator-(bignum &other) {
    bignum result;
    mpz_sub(result.value, value, other.value);
    return result;
}

bignum bignum::operator*(bignum &other) {
    bignum result;
    mpz_mul(result.value, value, other.value);
    return result;
}

pair<bignum, bignum> bignum::operator/(bignum &other) {
    bignum quotient;
    bignum remainder;
    mpz_cdiv_qr(quotient.value, remainder.value, value, other.value);
    return make_pair(quotient, remainder);
}

bignum bignum::operator%(bignum &other) {
    bignum result;
    mpz_mod(result.value, value, other.value);
    return result;
}

bignum bignum::operator^(unsigned long int &exponent) {
    bignum result;
    mpz_pow_ui(result.value, value, exponent);
    return result;
}

bool bignum::operator==(bignum &other) {
    int result = mpz_cmp(value, other.value);
    return (result == 0);
}

bool bignum::operator!=(bignum &other) {
    int result = mpz_cmp(value, other.value);
    return (result != 0);
}

bool bignum::operator<(bignum &other) {
    int result = mpz_cmp(value, other.value);
    return (result < 0);
}

bool bignum::operator>(bignum &other) {
    int result = mpz_cmp(value, other.value);
    return (result > 0);
}

bool bignum::operator<=(bignum &other) {
    int result = mpz_cmp(value, other.value);
    return (result <= 0);
}

bool bignum::operator>=(bignum &other) {
    int result = mpz_cmp(value, other.value);
    return (result >= 0);
}

bignum bignum::modpow(bignum &base, bignum &exponent, bignum &mod) {
    bignum result;
    mpz_powm(result.value, base.value, exponent.value, mod.value);
    return result;
}

bignum bignum::gcd(bignum &a, bignum &b) {
    bignum result;
    mpz_gcd(result.value, a.value, b.value);
    return result;
}

bignum bignum::modinv(bignum &a, bignum &p) {
    bignum result;
    mpz_invert(result.value, a.value, p.value);
    return result;
}

bignum bignum::parseBytes(unsigned char * bytes, size_t count) {
    //Example:
    //unsigned char a_bytes[2];
    //cryptoUtilities::secureRandom(a_bytes, 2);
    //bignum a = bignum::parseBytes(a_bytes, sizeof(a_bytes));
    bignum result;
    mpz_import(result.value, count, 0, sizeof(unsigned char), 0, 0, bytes);
    return result;
}

bignum bignum::parseHex(const char *hex) {
    bignum result;
    mpz_init_set_str(result.value, hex, 16);
    return result;
}
bignum bignum::parseStr(const char * str) {
    bignum result;
    mpz_init_set_str(result.value, str, 10);
    return result;
}

bignum bignum::operator+=(bignum &other) {
    mpz_add(value, value, other.value);
    return *this;
}

bignum bignum::operator-() {
    bignum result;
    mpz_neg(result.value, value);
    return result;
}

bignum bignum::operator*=(bignum &other) {
    mpz_mul(value, value, other.value);
    return *this;
}

string bignum::toStr() {
    char * str_array = mpz_get_str(nullptr, 10, value);
    string result(str_array);
    return result;
}

string bignum::toHex() {
    char * str_array = mpz_get_str(nullptr, 16, value);
    string result(str_array);
    return result;
}








