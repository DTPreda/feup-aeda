#include "packagingMachine.h"
#include <sstream>

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
	return 0;
}

// TODO
Box PackagingMachine::searchBox(Object& obj) {
	Box b;
	return b;
}

// TODO
unsigned PackagingMachine::packObjects() {
	return 0;
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
	return "";
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
	Box b;
	return b;
}