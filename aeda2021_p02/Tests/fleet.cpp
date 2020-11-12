#include "fleet.h"
#include <string>
#include <algorithm>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1) {
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

int Fleet::lowestYear() const {
    if(vehicles.size() == 0){
        return 0;
    }
    else{
        unsigned long int res = UINT64_MAX;
        for(auto x : vehicles){
            if(x->getYear() < res) {
                res = x->getYear();
            }
        }
        return res;
    }
}

ostream& operator<<(ostream& o, const Fleet& f){
    for(auto vehicle: f.vehicles){
        vehicle->info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator()(int yearM) const {
    vector<Vehicle *> res;
    for(auto vehicle: vehicles){
        if(vehicle->getYear() == yearM){
            res.push_back(vehicle);
        }
    }
    return res;
}

float Fleet::totalTax() const {
    float res = 0;
    for(auto vehicle: vehicles){
        res += vehicle->calculateTax();
    }
    return res;
}

unsigned Fleet::removeOldVehicles(int y1) {
    unsigned res = 0;
    for(auto vehicle: vehicles){
        if(vehicle->getYear() <= y1){
            vehicles.erase(remove(vehicles.begin(), vehicles.end(), vehicle), vehicles.end());
            res++;
            return res + removeOldVehicles(y1);
        }
    }
    return res;
}

