/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::ID = 1;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string nm) : name(nm){
    id = ID++;
}

bool BankOfficer::operator==(const BankOfficer &other) {
    return myAccounts == other.getAccounts() && name == other.getName() && id == other.getID();
}

bool operator>(const BankOfficer &first, const BankOfficer &second) {
    return first.myAccounts.size() > second.myAccounts.size() || (first.myAccounts.size() == second.myAccounts.size() && first.name > second.name);
}




