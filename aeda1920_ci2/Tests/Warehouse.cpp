#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    //TODO
    return 0;
}

Object Warehouse::RemoveObjectQueue(int maxSize){
     //TODO
     Object obj;
     return obj;
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    //TODO
    return 0;
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    //TODO
    vector<ThinTallBox> res;
    return res;
}

