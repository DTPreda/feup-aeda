#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game(){
    kids.clear();
}

// TODO
Game::Game(list<Kid>& l2){
    kids.clear();
    list<Kid>::iterator it;
    for(it = l2.begin(); it != l2.end(); it++){
        kids.push_back(*it);
    }
}

// TODO
void Game::addKid(const Kid &k1){
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const
{
    list<Kid> res;
    list<Kid>::const_iterator it;
    for(it = kids.begin(); it != kids.end(); it++){
        res.push_back(*it);
    }
    return res;
}

// TODO
string Game::write() const
{
    string res = "";
    for(auto kid : kids){
        res += kid.getName() + " : " + to_string(kid.getAge()) + "\n";
    }
    return res;
}

// TODO
Kid& Game::loseGame(string phrase)
{
    Kid *k1 = new Kid();
    list<Kid>::const_iterator it;
    list<Kid> res = kids;
    unsigned int counter = numberOfWords(phrase);
    while(res.size() > 1){
        it = res.begin();
        for(int i = 0; i < counter; i++){
            if(i == 0){ continue;}
            it++;
            if(it == res.end()){
                it = res.begin();
            }
        }
        res.erase(it);
    }
    *k1 = *(res.begin());
    return *k1;
}

// TODO
list<Kid>& Game::reverse()
{
   kids.reverse();
   return kids;
}

// TODO
list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;
    list<Kid>::const_iterator it;
    for(it = kids.begin(); it != kids.end(); ){
        if(it->getAge() > id){
            res.push_back(*it);
            kids.erase(it);
            it = kids.begin();
        }
        it++;
    }
    return res;
}

// TODO
void Game::setKids(const list<Kid>& l1){
    list<Kid>::const_iterator it;
    for(it = l1.begin(); it != l1.end(); it++){
        kids.push_back(*it);
    }
}

// TODO
bool Game::operator==(Game& g2)
{
    if(kids.size() != g2.kids.size()){
        return false;
    }
	list<Kid>::const_iterator it1, it2;
	it1 = kids.begin(), it2 = g2.kids.begin();
	for(; it1 != kids.end() && it2 != g2.kids.end(); it1++, it2++){
	    if(!(*it1 == *it2)){
            return false;
	    }
	}
	return true;
}

// TODO
list<Kid> Game::shuffle() const
{
    list<Kid> res;
    list<int> nums;
    for(int i = 0; i < kids.size(); i++){
        res.push_back(Kid());
    }
    int pos;
    list<Kid>::iterator it;
    for(auto kid: kids){
        pos = rand() % kids.size();
        while(find(nums.begin(), nums.end(), pos) != nums.end()){
            pos = rand() % kids.size();
        }
        nums.push_back(pos);
        it = res.begin();
        for(; pos > 0; pos--){
            it++;
        }
        *it = kid;
    }
    return res;
}
