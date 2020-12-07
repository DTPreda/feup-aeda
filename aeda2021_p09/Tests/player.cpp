#include "player.h"

void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const
{
    unsigned c = 0;
	for(auto it = bets.begin(); it != bets.end(); it++){
	    tabHInt bet = (*it).getNumbers();
	    for(auto betIt = bet.begin(); betIt != bet.end(); betIt++){
	        if(*betIt == num){
	            c++;
	        }
	    }
	}
	return c;
}

tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
	for(auto it = bets.begin(); it != bets.end(); it++){
	    if(it->countRights(draw) > 3){
	        res.insert(*it);
	    }
	}
	return res;
}
