#ifndef JACKPOT_H_
#define JACKPOT_H_

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Bet {
    vector<int> numbers;
    string player;
public:
    Bet(vector<int> ns, string p);
    vector<int> getNumbers() const;
    string getPlayer() const;
};

//---------------------------------

struct betHash
{
    // TODO
	int operator() (const Bet& b) const {
        int v = 0;
        for (int i : b.getNumbers()) {v = 37 * v + i;}
        return v;
	}

    // TODO
	bool operator() (const Bet& b1, const Bet& b2) const {
        return (sort(b1.getNumbers().begin(); b1.getNumbers().end()) == sort(b2.getNumbers().begin(); b2.getNumbers().end()) && b1.getPlayer() == b2.getPlayer());
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Jackpot
{
	tabHBet bets;
public:
	Jackpot();
	void addBet(const Bet& ap);
	unsigned betsInNumber(unsigned num) const;
	vector<string> drawnBets(vector<int> draw) const;
    unsigned getNumBets() const;
};

#endif 
