#include "packagingMachine.h"
#include <sstream>
#include <algorithm>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
	unsigned c = 0;
	for(auto it = objs.begin(); it != objs.end(); it++){
	    if(it->getWeight() <= boxCapacity){
	        objects.push(*it);
	        objs.erase(it);
	        c++; it--;
	    }
	}
	return c;
}

Box PackagingMachine::searchBox(Object& obj) {
    HeapBox temp, res;
    for(int i = boxes.size(); i > 0; i--){
        res.push(boxes.top());
        boxes.pop();
        if(res.top().getFree() >= obj.getWeight()){
            while(!temp.empty()){
                boxes.push(temp.top());
                temp.pop();
            }
            return res.top();
        }
        temp.push(res.top());
        res.pop();
    }
    boxes = temp;
    return Box(boxCapacity);
}

unsigned PackagingMachine::packObjects() {
    unsigned c = 0, isize, fsize;
    for(int i = objects.size(); i > 0; i--){
	    isize = boxes.size();
        Object obj = objects.top();
        objects.pop();
        Box bx = searchBox(obj);
        bx.addObject(obj);
	    addBox(bx);
	    fsize = boxes.size();
	    if(isize != fsize) c++;
	}
    return c;
}

string PackagingMachine::printObjectsNotPacked() const {
	if(objects.empty()) return "No objects!\n";
	stringstream res; Object obj(0,0); HeapObj temp = objects;
	for(int i = objects.size(); i > 0; i--){
	    obj = temp.top(); temp.pop();
	    res << obj << endl;
	}
	return res.str();
}

Box PackagingMachine::boxWithMoreObjects() const {
	if(boxes.empty()) throw MachineWithoutBoxes();
    Box b = boxes.top(); HeapBox temp = boxes;
    for(int i = temp.size(); i > 0; i--){
        temp.pop();
        if(temp.top().getNumObj() > b.getNumObj()){
            b = temp.top();
        }
    }
	return b;
}