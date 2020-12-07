#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

//TODO
struct betHash
{
	int operator() (const Bet& b) const
	{
        const tabHInt table = b.getNumbers();
        int hash = 0;
        for(auto it = table.begin(); it != table.end(); it++){
            hash += 43*hash + (*it)*37;
        }
        hash %= table.size();
        if(hash < 0) hash += table.size();
	    return hash;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
		const tabHInt first = b1.getNumbers(); const tabHInt second = b2.getNumbers();
		if(first.size() != second.size()){
		    return false;
		}
		tabHInt::const_iterator it;
		for(it = first.begin(); it != first.end(); it++){
            if(second.count(*it) == 0){
                return false;
            }
		}
		return true;
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
