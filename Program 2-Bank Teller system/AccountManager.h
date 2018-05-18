/*
* Sloan Kiechel
* ssk0006
* AccountManager.h
* AccountManager header to link AccountManager class
*/

#include <string>
#include <vector>
using namespace std;

#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

//AccountManager class. Holds a list of accounts and manages them.
class AccountManager {
	public:
		AccountManager(string filename); //Constructor
		AccountManager(); //Default constructor
		bool displayAccount(int accNum); //Displays account information
		bool addAccount(int accNum, string clName, int accType, int bal);
		bool withdraw(int accNum, int withdrawAmount);
		bool deposit(int accNum, int depositAmount);
		bool isAccount(int accNum);
	private:
		struct Account {
			//Constructor
			Account(int accNum, string clName, int accType, int bal) 
					: accountNum(accNum), clientName(clName), accountType(accType), balance(bal) {};
			int accountNum;
			string clientName;
			int accountType; //0 For checkings, 1 for Savings
			int balance; 
		};
		static const string DEFAULT_FILE;
		vector<Account> accountList;
		string accountFile;
		void loadAccounts();
		void saveAccounts();
};

//const string AccountManager::DEFAULT_FILE = "account-info";

#endif