#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>
#include <algorithm>

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

class NoSuchFloorException {
public:
    int floor;
    NoSuchFloorException(int f) : floor(f) {};
    int getFloor() { return floor;}
};


template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if(chambers.size() < maxCapacity){
        for(auto& hotelChamber : chambers){
            if(*chamber == *hotelChamber){
                return false;
            }
        }
        chambers.push_back(chamber);
        return true;
    }
    return false;
}


//TODO
template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    std::sort(chambers.begin(), chambers.end(), [](Chamber* first, Chamber* second){return second < first;});
}

//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {
    for(auto chamber : chambers){
        if(chamber->getCode() == code && chamber->getFloor() == floor){
            chambers.erase(remove(chambers.begin(), chambers.end(), chamber), chambers.end());
            return chamber;
        }
    }
    throw NoSuchChamberException();
}

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    float avg = 0; int counter = 0;
    for(auto chamber : chambers){
        if(chamber->getFloor() == floor) {
            avg += chamber->getArea();
            counter++;
        }
    }
    if(counter) return avg/counter;
    throw NoSuchFloorException(floor);
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    for(auto chamber : chambers){
        if(chamber->getCode() == code && chamber->getFloor() == floor){
            if(chamber->getReservation()) return false;
            chamber->setReservation(true);
            reservationsDone.push_back(*chamber);
            return true;
        }
    }
    return false;
}

//TODO
template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    bool res;
    std::list<Chamber> never;
    for(auto chamber : chambers){
        res = false;
        for(auto reserved : reservationsDone){
            if(*chamber == reserved){
                res = true;
                break;
            }
        }
        if(!res){
            never.push_back(*chamber);
        }
    }
    return never;
}


#endif /* SRC_HOTEL_H_ */
