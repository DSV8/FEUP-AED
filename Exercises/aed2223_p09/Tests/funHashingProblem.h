#ifndef SRC_FUNHASHINGPROBLEM_H
#define SRC_FUNHASHINGPROBLEM_H

#include <iostream>
#include <vector>
using namespace std;

class FunHashingProblem{
public:
    FunHashingProblem();
    static vector<int> findDuplicates(const vector<int>& values, int k);
};

#endif