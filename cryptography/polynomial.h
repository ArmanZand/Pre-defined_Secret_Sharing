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
    bracket(vector<member> & input_members);
    bracket(initializer_list<member> input_members);
    vector<member> members;
    bracket operator*(bracket & other);
};

struct point {
public:
    point(bignum & from, bignum & to, bignum & value) : x(from), y(to), z(value) {}
    point(int from, int value) : x(bignum(from)), z(bignum(value)), y(0) {}
    point(bignum & from, bignum & value) : x(from), z(value), y(0) {}
    bignum x; //from node
    bignum y; //to node
    bignum z; //value
};
//polynomial usage example
//    bignum prime(97);
//    polynomial p(&prime);
//    vector<point> points = { point(0, 5), point(1,10), point(2,20) };
//    p.interpolate(points);
//
//    point res = p.evaluate(0);
//    cout << res.z << endl;

class polynomial {
private:
    bignum p;
    vector<bignum> coeffs;
    vector<bracket> expandBrackets(vector<vector<bignum>> & bracketStructure);
    void reconstructPolynomial(vector<point> & points);
public:
    polynomial(const bignum * prime);
    polynomial(const bignum * prime, vector<bignum> coefficients);
    vector<bignum> & polynomial::interpolate(vector<point>  & points);
    point evaluate(bignum & x);
    point evaluate(int x);
};



#endif //CLEAN_SOCKETS_POLYNOMIAL_H
