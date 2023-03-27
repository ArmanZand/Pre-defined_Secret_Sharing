//
// Created by arman on 27/03/2023.
//

#include "polynomial.h"
polynomial::polynomial(const bignum *prime) {
    p = *prime;
}

bracket bracket::operator*(bracket &other) {
    vector<member> result;
    for(member & thisM: members){
        for(member & otherM : other.members){
            bignum member_value = thisM.num* otherM.num;
            bignum member_degree = thisM.deg + otherM.deg;
            member newMember(member_value, member_degree);
            result.push_back(newMember);
        }
    }
    for(int i = result.size(); i  --> 0;){
        for (int j = result.size(); j --> 0;){
            if( i != j && result[i].deg == result[j].deg){
                result[i].num += result[j].num;
                result.erase(result.begin() + j);
            }
        }
    }
    return bracket(result);
}

bracket::bracket(vector<member> &input_members) {
    bracket::members = input_members;
}

bracket::bracket(initializer_list<member> input_members) {
    bracket::members = input_members;
}

vector<bignum> polynomial::interpolate(vector<point> points) {
    return polynomial::reconstructPolynomial(points);
}

vector<bracket> polynomial::expandBrackets(vector<vector<bignum>> bracketStructure) {
    vector<bracket> expandedBrackets;
    for(int i = 0; i < bracketStructure.size(); i++){
        expandedBrackets.push_back({ member(bignum(1), bignum("1")), member(bracketStructure[i][0],0) });
        for (int j = 0; j < bracketStructure[i].size() - 1; j++){
            bracket b({member(1,1), member(bracketStructure[i][j+1], 0)});
            expandedBrackets[i] = expandedBrackets[i] * b;
        }
    }
    return expandedBrackets;
}

vector<bignum> polynomial::reconstructPolynomial(vector<point> & points) {
    vector<vector<bignum>> brackets;
    vector<bignum> divisors;

    for(int j = 0; j < points.size(); j++){
        brackets.push_back(vector<bignum>());
        divisors.push_back(1);
        for(int m = 0; m < points.size(); m++){
            if(m != j){
                brackets[j].push_back(-points[m].x);
                bignum x_diff = (points[j].x - points[m].x);
                divisors[j] *= x_diff;
            }
        }
    }

    vector<bracket> expandedBrackets = polynomial::expandBrackets(brackets);
    vector<bignum> polyCoeffs(expandedBrackets.size());
    for(int i = 0; i < expandedBrackets.size(); i++){
        for(int j = 0; j < expandedBrackets[i].members.size(); j++){
            expandedBrackets[i].members[j].num = expandedBrackets[i].members[j].num * points[i].z;

            bignum divisor(divisors[i] % p);
            bignum div_inv = bignum::modinv(divisor, p);
            bignum compute_div = expandedBrackets[i].members[j].num * div_inv;
            polyCoeffs[expandedBrackets[i].members.size() - j - 1] += compute_div;
            polyCoeffs[expandedBrackets[i].members.size() - j - 1]  = polyCoeffs[expandedBrackets[i].members.size() - j - 1] % p;
        }
    }
    return polyCoeffs;
}

