#include "funListProblem.h"
#include <algorithm>

FunListProblem::FunListProblem() {}


//-----------------------------------------------------------------

// TODO
list<int> FunListProblem::removeHigher(list<int> &values, int x) {
    list<int> l1;
    list<int>::iterator it = values.begin();

    while (it != values.end()) {
        if (*it > x) {l1.push_back(*it); it = values.erase(it);}
        else {it++;}
    }
    return l1;
}



//TODO
list<pair<int,int>> FunListProblem::overlappingIntervals(list<pair<int,int>> values) {
    list<pair<int,int>> res;
    if (values.empty()) {return res;}
    values.sort();
    list<pair<int,int>>::iterator it = values.begin();
    res.push_back(*it); it++;

    for (; it != values.end(); it++) {
        if (it->first <= res.back().second) {res.back().second = max(res.back().second, it->second);}
        else {res.push_back(*it);}
    }
    return res;
}
