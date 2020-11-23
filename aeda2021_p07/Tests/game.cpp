#include "game.h"
#include <sstream>
#include <math.h>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}

int pow(int n, int p){
    if(p == 0){
        return 1;
    }
    int res = n;
    for(int i = 1; i < p; i++){
        res = res*n;
    }
    return res;
}


Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    BinaryTree<Circle> temp(Circle(points[0], states[0]));
    vector<BinaryTree<Circle>> trees;
    int left = 1, elem, check = 0;
    while(2*left + 1 < points.size()){
        left = 2*left + 1;
    }
    left = (left - 1)/2; // maximum leftmost node that isn't a leaf
    for(int i = 0; i < pow(2, h - 1); i++){ // builds base binary trees
        trees.push_back(BinaryTree<Circle>(Circle(points[left], states[left]), Circle(points[2*left + 1], states[2*left + 1]), Circle(points[2*left + 2], states[2*left + 2])));
        left++;
    }
    h--;
    while(trees.size() != 1){ // merges binary trees together, bottom up, to form the main tree, connecting to the root
        if(trees.size() == 2){
            trees[0] = BinaryTree<Circle>(Circle(points[0], states[0]), trees[0], trees[1]);
            check = 1;
        }
        for(int j = 0; j < trees.size()/2 && !check; j++){
            elem = pow(2, h-1) - 1 + j;
            trees[j] = BinaryTree<Circle>(Circle(points[elem], states[elem]), trees[2*j], trees[2*j + 1]);
        }
        trees.resize(trees.size()/2);
    }
    game = trees[0];
}


string Game::writeGame()
{
	BTItrLevel<Circle> it(game);
	string res = "";
	for( ; !it.isAtEnd(); it.advance()){
        res += to_string(it.retrieve().getPoints()) + "-";
        if(it.retrieve().getState()){
            res += "true";
        } else {
            res += "false";
        }
        res += "-" + to_string(it.retrieve().getNVisits()) + "\n";
	}
	return res;
}


int Game::move()
{
    BTItrLevel<Circle> it(game), res(game);
    int pos = 0, lastPos;
    while (true){
        lastPos = pos;
        if(it.retrieve().getState()){
            pos = 2*lastPos + 2;
        } else {
            pos = 2*lastPos + 1;
        }
        it.retrieve().changeState(); it.retrieve().incrementVisits();
        for(int i = 0; i < pos - lastPos && !it.isAtEnd(); it.advance(), i++){}
        if(it.isAtEnd()){
            pos = lastPos;
            break;
        }
    }
    for(int j = 0; j < pos; j++) {
        res.advance();
    }
    return res.retrieve().getPoints();
}


int Game::mostVisited()
{
    int res = 0;
    BTItrLevel<Circle> it(game);
    it.advance();
    while(!it.isAtEnd()){
        if(it.retrieve().getNVisits() > res){
            res = it.retrieve().getNVisits();
        }
        it.advance();
    }
	return res;
}
