#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

//TODO
Client::Client() {
    numGifts = (rand() % 5) + 1;
}

//TODO
unsigned Client::getNumGifts() const {
    return numGifts;
}


//TODO
Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime = 0;
    nextLeave = 0;
    nextEnter = (rand() % 20) + 1;
    numAttendedClients = 0;
}

//TODO
unsigned Counter::getActualTime() const {
    return actualTime;
}

//TODO
unsigned Counter::getNextEnter() const {
    return nextEnter;
}

//TODO
unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

//TODO
unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

//TODO
unsigned Counter::getNextLeave() const {
    return nextLeave;
}

//TODO
Client & Counter::getNextClient() {
    Client *cl = new Client();
    if(clients.empty()){
        throw EmptyQueue();
    }
    *cl = clients.front();
    return *cl;
}

//TODO
void Counter::enter()
{
    Client cl;
    if(clients.empty()){
        nextLeave = actualTime + cl.getNumGifts() * wrappingTime;
    }
    clients.push(cl);
    nextEnter = (rand() % 20) + 1;
    cout << "time = " << actualTime << "\nnext costumer arrived with " << cl.getNumGifts() << " gifts\n";
}

//TODO
void Counter::leave()
{
    Client cl = getNextClient();
    clients.pop();
    nextLeave = actualTime + clients.front().getNumGifts() * wrappingTime;
    numAttendedClients++;
    cout << "time = " << actualTime << "\nlast costumer left with " << cl.getNumGifts() << " gifts\n";
}

//TODO
void Counter:: nextEvent()
{
    if(nextEnter < nextLeave || clients.empty()){
        nextLeave -= nextEnter;
        actualTime += nextEnter;
        enter();
    }
    else {
        nextEnter -= nextLeave;
        actualTime += nextLeave;
        leave();
    }
}


//TODO
ostream & operator << (ostream & out, const Counter & c2)
{
    out << "Attended Clients: " << c2.numAttendedClients << endl;
    out << "Clients currently waiting: " << c2.clients.size() << endl;
    return out;
}


