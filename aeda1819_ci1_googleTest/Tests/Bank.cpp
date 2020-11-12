/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
	double res = 0;
    for(auto account : accounts){
	    if(account->getCodH() == cod1){
	        res += account->getWithdraw();
	    }
	}
    return res;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for(auto& officer : bankOfficers){
	    if(officer.getName() == name){
	        res = officer.getAccounts();
	        bankOfficers.erase(std::remove(bankOfficers.begin(), bankOfficers.end(), officer), bankOfficers.end());
	        break;
	    }
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *bo= new BankOfficer();
    bo->setName("INVALID");
    for(auto officer : bankOfficers){
        if(officer.getName() == name){
            officer.addAccount(ac);
            *bo = officer;
            break;
        }
    }
    if(bo->getName() == "INVALID"){
        throw NoBankOfficerException(name);
    }
    return *bo;
}


// a alterar
void Bank::sortAccounts() {
    bool check;
    Account* ac = new Account;
    for(unsigned int i = accounts.size() - 1; i > 0; i--){
        check = false;
        for(unsigned int j = 0; j < i; j++)
            if(accounts[j+1]->getBalance() < accounts[j]->getBalance() || (accounts[j+1]->getBalance() == accounts[j]->getBalance() && accounts[j+1]->getCodIBAN() < accounts[j]->getCodIBAN())){
                *ac = *accounts[j];
                *accounts[j] = *accounts[j+1];
                *accounts[j+1] = *ac;
                check = true;
            }
        if(!check) return;
    }
}

