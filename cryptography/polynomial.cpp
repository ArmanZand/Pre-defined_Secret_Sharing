//
// Created by arman on 27/03/2023.
//

#include "polynomial.h"

void polynomial::interpolate(vector<point> * points) {
    for (const point & p: *points) {

    }

}

polynomial::polynomial(const bignum *prime, int *threshold) {
    p = *prime;
    t = *threshold;
}

bracket bracket::multiplyWith(bracket &other) {
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
