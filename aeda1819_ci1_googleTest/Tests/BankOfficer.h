/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
    static unsigned int ID;
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;

	//-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);
	bool operator==(const BankOfficer& other);
	friend bool operator>(const BankOfficer& first, const BankOfficer& second);
};

#endif /* SRC_BANKOFFICER_H_ */
