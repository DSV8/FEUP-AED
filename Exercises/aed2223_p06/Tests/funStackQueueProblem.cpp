#include "funStackQueueProblem.h"
#include "cell.h"

FunStackQueueProblem::FunStackQueueProblem() {}


//-----------------------------------------------------------------

// TODO
vector<string> FunStackQueueProblem::binaryNumbers(int n) {
    vector<string> res;
    queue<string> q;
    q.push("1");
    for (int i = 0; i < n; i++) {
        string s = q.front();
        q.pop();
        res.push_back(s);
        q.push(s + "0");
        q.push(s + "1");
    }
    return res;
}


//TODO
vector<int> FunStackQueueProblem::calculateSpan(vector<int> prices)
{
    vector<int> res;
    return res;
}


//TODO
int FunStackQueueProblem::knightJumps(int initialPosx, int initialPosy, int targetPosx, int targetPosy, int n) {
    return -1;
}






