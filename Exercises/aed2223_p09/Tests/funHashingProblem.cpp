#include "funHashingProblem.h"
#include <unordered_set>

FunHashingProblem::FunHashingProblem() {}

// -------------------------------------

// TODO
vector<int> FunHashingProblem::findDuplicates(const vector<int>& values, int k) {
    vector<int> res;
    unordered_set <int> window;

    for (int i = 0; i < values.size(); i++){
        if (window.find(values[i]) != window.end()){res.push_back(values[i]);}
        window.insert(values[i]);
        if (i >= k) {window.erase(values[i-k]);}
    }
    return res;
}