#include "game.h"
#include <sstream>


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

//TODO
Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    BinaryTree<Circle> temp(Circle(points[0], states[0]));
    vector<BinaryTree<Circle>> trees;
    int left = 1, elem;
    while(2*left + 1 < points.size()){
        left = 2*left + 1;
    }
    left = (left - 1)/2;//maximum leftmost node that isn't a leaf
    for(int i = 0; i < pow(2, h - 1); i++){
        trees.push_back(BinaryTree<Circle>(Circle(points[left], states[left]), Circle(points[2*left + 1], states[2*left + 1]), Circle(points[2*left + 2], states[2*left + 2])));
    }
    h--;
    while(trees.size() != 1){
        if(trees.size() == 2){
            trees[0] = BinaryTree<Circle>(Circle(points[0], states[0]), trees[0], trees[1]);
        }
        for(int j = 0; j < trees.size()/2 - 1; j++){
            elem = pow(2, h-1) - 1 + j;
            trees[j] = BinaryTree<Circle>(Circle(points[elem], states[elem]), trees[2*j], trees[2*j + 1]);
        }
        trees.resize(trees.size()/2);
    }
    game = trees[0];
}


//TODO
string Game::writeGame()
{
	return "";
}


//TODO
int Game::move()
{
	return 0;
}


//TODO
int Game::mostVisited()
{
	return 0;
}
