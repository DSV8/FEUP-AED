#include "funSortProblem.h"
#include <algorithm>
#include <limits.h>
#include <tclDecls.h>

FunSortProblem::FunSortProblem() {}


//-----------------------------------------------------------------

// TODO
void FunSortProblem::expressLane(vector<Product> &products, unsigned k) {
    if (products.size() <= k) {return;}
    sort(products.begin(),products.end());
    products.erase(products.begin() + k, products.end());
}

// TODO
int FunSortProblem::minDifference(const vector<unsigned> &values, unsigned nc) {
    vector<unsigned> val(values);
    if (val.size() < nc) {return -1;}
    sort(val.begin(), val.end());
    unsigned start = 0;
    unsigned end = nc - 1;
    unsigned mini = INT_MAX;
    while(end < val.size()) {
        mini = min(mini, val(end) - val(start));
        start++;
        end++;
    }
    return mini;
}


// TODO
unsigned FunSortProblem::minPlatforms (const vector<float> &arrival, const vector<float> &departure) {
    return 0;
}

//TODO
unsigned FunSortProblem::numInversions(vector <int> v) {
    return 0;
}

// TODO
void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {
}

