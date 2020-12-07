#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


bool Bet::contains(unsigned num) const
{
	return numbers.count(num) != 0;
}

void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    for(int i = 0, c = 0; c < n && i < values.size(); i++){
        if(numbers.count(values[i]) == 0){
            numbers.insert(values[i]);
            c++;
        }
    }
}

unsigned Bet::countRights(const tabHInt& draw) const
{
    unsigned c = 0;
	tabHInt::const_iterator nIt, dIt;
	for(nIt = numbers.begin(); nIt != numbers.end(); nIt++){
        if(draw.count(*nIt) != 0){
            c++;
        }
	}
	return c;
}
