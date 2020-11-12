#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y) : brand(b), month(m), year(y) {}

Vehicle::~Vehicle() {}

MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl) : Vehicle(b, m , y), fuel(f), cylinder(cyl) {}

Car::Car(string b, int m, int y, string f, int cyl) : MotorVehicle(b, m, y, f, cyl) {}

Truck::Truck(string b, int m, int y, string f, int cyl, int ml) : MotorVehicle(b, m, y, f, cyl), maximumLoad(ml) {}

Bicycle::Bicycle(string b, int m, int y, string t) : Vehicle(b, m , y), type(t) {}

string MotorVehicle::getFuel() const {
    return fuel;
}

string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::info() const {
    cout << "Brand: " << brand << endl;
    cout << "Date: " << month << "/" << year << endl;
    return 3;
}

int MotorVehicle::info() const {
    Vehicle::info();
    cout << "Fuel: " << fuel << endl << "Cylinder: " << cylinder << endl;
    return 5;
}

int Car::info() const{
    MotorVehicle::info();
    cout << endl;
    return 5;
}

int Truck::info() const {
    MotorVehicle::info();
    cout << "Maximum Load: " << maximumLoad << endl << endl;
    return 6;
}

int Bicycle::info() const {
    Vehicle::info();
    cout << "Type: " << type << endl << endl;
    return 4;
}

int Vehicle::info(ostream& o) const {
    o << "Brand: " << brand << endl;
    o << "Date: " << month << "/" << year << endl;
    return 3;
}

int MotorVehicle::info(ostream& o) const {
    Vehicle::info(o);
    o << "Fuel: " << fuel << endl << "Cylinder: " << cylinder << endl;
    return 5;
}

int Car::info(ostream& o) const{
    MotorVehicle::info(o);
    o << endl;
    return 5;
}

int Truck::info(ostream& o) const {
    MotorVehicle::info(o);
    o << "Maximum Load: " << maximumLoad << endl << endl;
    return 6;
}

int Bicycle::info(ostream& o) const {
    Vehicle::info(o);
    o << "Type: " << type << endl << endl;
    return 4;
}

bool Vehicle::operator<(const Vehicle &v) const {
    return year < v.year || (year == v.year && month < v.month);
}

float Vehicle::calculateTax() const {}

float MotorVehicle::calculateTax() const {
    if((fuel == "gas" && cylinder <= 1000) || (fuel != "gas" && cylinder <= 1300)){
        if(year > 1995){
            return 14.96;
        }
        else {
            return 8.10;
        }
    }
    else if((fuel == "gas" && cylinder <= 1300) || (fuel != "gas" && cylinder <= 2000)){
        if(year > 1995){
            return 29.06;
        }
        else {
            return 14.56;
        }
    }
    else if((fuel == "gas" && cylinder <= 1750) || (fuel != "gas" && cylinder <= 3000)){
        if(year > 1995){
            return 45.15;
        }
        else {
            return 22.65;
        }
    }
    else if((fuel == "gas" && cylinder <= 2600) || (fuel != "gas" && cylinder > 3000)){
        if(year > 1995){
            return 113.98;
        }
        else {
            return 54.89;
        }
    }
    else if(fuel == "gas" && cylinder <= 3500){
        if(year > 1995){
            return 181.17;
        }
        else {
            return 87.13;
        }
    }
    else if(fuel == "gas" && cylinder > 3500){
        if(year > 1995){
            return 320.89;
        }
        else {
            return 148.37;
        }
    }
}

float Bicycle::calculateTax() const {
    return 0;
}