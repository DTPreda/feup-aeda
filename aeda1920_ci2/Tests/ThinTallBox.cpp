#include "ThinTallBox.h"
#include "WideFlatBox.h"
#include <algorithm>

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize()-next_object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}


void ThinTallBox::insert(Object object) {
    if(getContentSize() + object.getSize() <= getCapacity()){
        objects.push(object);
        setContentSize(getContentSize() + object.getSize());
        return;
    }
    throw ObjectDoesNotFitException();
}

bool ThinTallBox::sortedCheck(){
    stack<Object> temp = objects;
    double size = temp.top().getSize();
    temp.pop();
    while(!temp.empty()){
        if(size > temp.top().getSize()){
            return false;
        }
        size = temp.top().getSize();
        temp.pop();
    }
    return true;
}

void ThinTallBox::sortObjects() {
    stack<Object> temp;
    Object middleStep;
    double size;
    while(!sortedCheck()){
        size = 0;
        while(objects.top().getSize() >= size){
            size = objects.top().getSize();
            temp.push(objects.top());
            objects.pop();
        }
        size = objects.top().getSize();
        middleStep = objects.top();
        objects.pop();
        while(!temp.empty()){
            objects.push(temp.top());
            temp.pop();
        }
        objects.push(middleStep);
    }
}
