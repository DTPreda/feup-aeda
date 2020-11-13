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
    sort(obj.begin(), obj.end(), [](Object& first, Object& second){
        return second.getSize() < first.getSize();
    });
    for(auto object : obj){
        objects.push(object);
    }
    return obj.size();
}

Object Warehouse::RemoveObjectQueue(int maxSize){
     Object obj("dummy", maxSize);
     queue<Object> temp;
     while(objects.front().getSize() > maxSize && !objects.empty()){
         temp.push(objects.front());
         objects.pop();
     }
     if(!objects.empty()){
         obj = objects.front();
         objects.pop();
         while(!objects.empty()){
             temp.push(objects.front());
             objects.pop();
         }
     }
    while(!temp.empty()){
        objects.push(temp.front());
        temp.pop();
    }
    return obj;
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for(auto& box : boV){
        boxes.push(box);
    }
    return boxes.size();
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    queue<ThinTallBox> temp;
    while(!boxes.empty()){
        ThinTallBox box = boxes.front();
        boxes.pop();
        if(box.full()){
            res.push_back(box);
            continue;
        }
        else if(box.getContentSize() < box.getCapacity()){
            Object obj = RemoveObjectQueue(box.getCapacity() - box.getContentSize());
            if(obj.getName() != "dummy"){
                box.insert(obj);
            }
            else{
                box.insert(Object("dummy", 0));
            }
        }
        if(box.getDays() == 0){
            res.push_back(box);
            continue;
        }
        temp.push(box);
    }
    while(!temp.empty()){
        boxes.push(temp.front());
        temp.pop();
    }
    return res;
}

