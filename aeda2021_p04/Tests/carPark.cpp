#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include "quickSort.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli) {
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const {
    return clients;
}

unsigned CarPark::getNumPlaces() const {
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const {
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const {
    return numMaxClients;
}

unsigned CarPark::getNumClients() const {
    return clients.size();
}

bool operator==(const InfoCard& first, InfoCard& second){
    return first.name == second.name;
}

int CarPark::clientPosition(const string & name) const {
    int pos;
    for(auto client : clients){
        if(client.name == name){
            if((pos = sequentialSearch(clients, client)) != -1){
                return pos;
            }
            break;
        }
    }
    return -1;
}

unsigned CarPark::getFrequency(const string &name) const {
    int pos;
    if((pos = clientPosition(name)) != -1){
        return clients[pos].frequency;
    }
    throw ClientDoesNotExist(name);
}

// TODO: to modify
bool CarPark::addClient(const string & name) {
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    clients.push_back(info);
    return true;
}

// TODO: to modify
bool CarPark::removeClient(const string & name) {
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name) {
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;
    freePlaces--;
    return true;
}

// TODO: to modify
bool CarPark::leave(const string & name) {
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


InfoCard CarPark::getClientAtPos(unsigned p) const {
    InfoCard info;
    return info;
}

bool freqSort(InfoCard& first, InfoCard& second){
    return first.frequency > second.frequency || (first.frequency == second.frequency && first.name < second.name);
}

void CarPark::sortClientsByFrequency()
{
    insertionSort(clients, freqSort);
}

vector<string> CarPark::clientsBetween(unsigned int f1, unsigned int f2) {
    sortClientsByFrequency();
    vector<string> res;
    for(auto client : clients){
        if(client.frequency >= f1 && client.frequency <= f2){
            res.push_back(client.name);
        }
    }
    return res;
}

bool nameCrescent(InfoCard& first, InfoCard& second){
    return first.name < second.name;
}

InfoCard& InfoCard::operator=(const InfoCard &second) {
    name = second.name;
    present = second.present;
    frequency = second.frequency;
    return *this;
}

void CarPark::sortClientsByName() {
    quickSort(clients, nameCrescent);
}