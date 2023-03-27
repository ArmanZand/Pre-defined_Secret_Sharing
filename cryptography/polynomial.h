//
// Created by arman on 27/03/2023.
//

#ifndef CLEAN_SOCKETS_POLYNOMIAL_H
#define CLEAN_SOCKETS_POLYNOMIAL_H
#include "../bignum/bignum.h"
#include <vector>
using namespace std;

struct member {
public:
    member(const bignum & number,const bignum & degree) : num(number) , deg(degree) {}
    bignum num;
    bignum deg;

};

struct bracket {
public:
    bracket(vector<member> & members) : members(members) {}
    vector<member> members;
    bracket multiplyWith(bracket & other);
};

struct point {
public:
    point(bignum & from, bignum & to, bignum & value) : x(from), y(to), z(value) {}
    const bignum x; //from node
    const bignum y; //to node
    const bignum z; //value
};

class polynomial {
private:
    int t;
    bignum p;
public:
    polynomial(const bignum * prime, int * threshold);
    void polynomial::interpolate(vector<point> * points);
};



#endif //CLEAN_SOCKETS_POLYNOMIAL_H
