/*
* Sloan Kiechel
* ssk0006
* AccountManager.cpp
*
* to compile:
* g++ -o AccountManager AccountManager.cpp
* NOTE: This is only for AccountManager testing. You must uncomment #define UNIT_TESTING below. 
* To compile/run the whole project, see System.cpp
* 
* c/Users/sloan/Dropbox/Spring_2018/Software_Construction/Project2
*
* Extra resource(s):
* http://www.cplusplus.com/forum/general/51349/ find/remove windows line ending /r from getline.
* http://www.cplusplus.com/reference/cstdlib/atoi/ String to Int
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;

//For testing. Comment out when not testing.
//#define UNIT_TESTING

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
		/******************************************************************************/
		/****************************Test Functions************************************/
		/******************************************************************************/
		#ifdef UNIT_TESTING
		friend void test_loadAccounts();
		friend void test_saveAccounts();
		friend void test_addAccount();
		friend void test_withdraw();
		friend void test_deposit();
		#endif
};

//Default file
const string AccountManager::DEFAULT_FILE = "account-info.txt";

//Main testing
#ifdef UNIT_TESTING
//Test Prototypes
void test_loadAccounts();
void test_saveAccounts();
void test_addAccount();
void test_withdraw();
void test_deposit();

int main() {
	test_loadAccounts();
	test_saveAccounts();
	test_addAccount();
	test_withdraw();
	test_deposit();
	
	//Test display
	AccountManager am("loadAccount.txt");
	am.displayAccount(123456);
}
#endif

//Default constructor, sets file to default file, load account list.
AccountManager::AccountManager() {
	accountFile = DEFAULT_FILE;
	loadAccounts(); //Load accounts
}

//Constructor. Sets file then loads accounts from the file.
AccountManager::AccountManager(string filename) {
	accountFile = filename;
	loadAccounts(); //Load accounts
}

//Load accounts from file
void AccountManager::loadAccounts() {
	ifstream inStream;
	inStream.open((char*)accountFile.c_str());
	//If cannot find or open, display error
	if (inStream.fail()) {
		cout << "\tCannot open " << accountFile << endl;
	}
	else {
		//Retrieve Account info
		int accNum, accType, bal;
		string clName, tempNum, tempType, tempBal; //Use temps to store string from getline, then convert to int and put in place.
		//Puts data into placeholders from the file, then pushes this data into a new 
		//account in the account list.
		while (getline(inStream, tempNum)) {
			getline(inStream, clName);
			getline(inStream, tempType);
			getline(inStream, tempBal);
			/*Windows adds an /r To the end of the file. I've never had it be an issue with getline() before,
			* but it was causing an issue this time, so this code corrects it incase a \r is read */
			if (clName.at(clName.size() -1) == '\r') {
				clName.erase(clName.size()-1);
			}
			//convert string to integer
			accNum = atoi(tempNum.c_str());
			accType = atoi(tempType.c_str());
			bal = atoi(tempBal.c_str());
			//Add account to account list
			accountList.push_back(Account(accNum, clName, accType, bal));
		}
	}
	inStream.close(); //Close file
}

//Save accounts to file
void AccountManager::saveAccounts() {
	ofstream outStream;
	outStream.open((char*)accountFile.c_str());
	//if fails, display error
	if (outStream.fail()) {
		cout << "\tCannot save account list to file " << accountFile << endl;
	}
	//Else, input account list to file
	else {
		for (int i = 0; i < accountList.size(); i++) {
			outStream << accountList[i].accountNum << endl;
			outStream << accountList[i].clientName << endl;
			outStream << accountList[i].accountType << endl;
			outStream << accountList[i].balance << endl;
		}
	}
	outStream.close(); //Close file
}

//Displays accounts. True if found and displayed, false if account does not exist.
bool AccountManager::displayAccount(int accNum) {
	//Search for account
	for (int i = 0; i < accountList.size(); i++) {
		//Account exists, display data
		if (accNum == accountList[i].accountNum) {
			cout << "\t" << accountList[i].clientName << "'s ";
			if (accountList[i].accountType == 0) {
				cout << "Checkings Account #";
			}
			else {
				cout << "Savings account #";
			}
			cout << accNum << endl;
			cout << "\tBalance: $" << accountList[i].balance << endl;
			return true;
		}
	}
	//If reach here, account never found
	cout << "\tAccount " << accNum << " does not exist\n";
	return false;
}

//Adds an account. Returns true if the account successfully made and saved.
//False if account already exists, if client name is empty, if type is a value other than 0 or 1,
//or if balance is less than 0.
//System must ensure client exists before adding the account.
bool AccountManager::addAccount(int accNum, string clName, int accType, int bal) {
	//Check for valid name
	if (clName == "") {
		cout << "\tClient name cannot be empty!\n";
		return false;
	}
	//Check for valid account type
	//0 is checkings, 1 is savings
	if (accType != 0 && accType != 1) {
		cout << "\tInvalid account type\n";
		return false;
	}
	//check for valid balance amount
	if (bal < 0) {
		cout << "\tBalance cannot be less than zero\n";
		return false;
	}
	//Search for account
	for (int i = 0; i < accountList.size(); i++) {
		if (accNum == accountList[i].accountNum) {
			cout << "\tAccount " << accNum << " already exists. No account added\n";
			return false;
		}
	}
	//If everything valid, add account and save.
	accountList.push_back(Account(accNum, clName, accType, bal));
	saveAccounts();
	cout << "\tAccount added and saved to account file\n";
	return true;
}

//Withdraws money. Returns true if successful.
//Returns false if account does not exist, or withdrawAmount not valid
bool AccountManager::withdraw(int accNum, int withdrawAmount) { 
	//Ensure withdrawAmount is more than 0.
	if (withdrawAmount <= 0) {
		cout << "\tAmount must be greater than 0\n";
		return false;
	}
	//Search for account
	for (int i = 0; i < accountList.size(); i++) {
		//Account exists
		if (accNum == accountList[i].accountNum) {
			//Ensure withdraw amount is valid
			if (withdrawAmount > accountList[i].balance) {
				cout << "\tCannot withdraw more than account balance\n";
				return false;
			}
			//Withdraw amount is valid. Withdraw and save.
			accountList[i].balance -= withdrawAmount;
			cout << "\t$" << withdrawAmount << " withdrawn\n";
			saveAccounts();
			return true;
		}
	}
	//If code gets here, account does not exist.
	cout << "\tAccount " << accNum << " does not exist\n";
	return false;
}

//Deposit money, returns true if successful.
//Returns false if account does not exist or depositAmount not valid.
bool AccountManager::deposit(int accNum, int depositAmount) {
	//Ensure depositAmount is more than 0.
	if (depositAmount <= 0 || depositAmount > 100000) {
		cout << "\tAmount must be greater than 0 and cannot be greater than $100,000\n";
		return false;
	}
	//Search for account
	for (int i = 0; i < accountList.size(); i++) {
		if (accNum == accountList[i].accountNum) {
			//Deposit and save
			accountList[i].balance += depositAmount;
			cout << "\t$" << depositAmount << " deposited\n";
			saveAccounts();
			return true;
		}
	}
	//If code gets here, account does not exist.
	cout << "\tAccount " << accNum << " does not exist\n";
	return false;
}

//Returns true if account exists, false otherwise.
bool AccountManager::isAccount(int accNum) {
	for (int i = 0; i < accountList.size(); i ++) {
		if (accNum = accountList[0].accountNum) {
			return true;
		}
	}
	//If it gets here, does not exist.
	return false;
}

/**************************************************************************************************/
/**********************************************TESTING*********************************************/
/**************************************************************************************************/
#ifdef UNIT_TESTING
//Load accounts test
void test_loadAccounts() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	cout << "loadAccounts() testing \n";
	//Test 1: Empty file
	cout << "\tTest 1: Empty file\n";
	AccountManager am("empty-file.txt");
	assert("empty-file.txt" == am.accountFile);
	assert(0 == am.accountList.size());
	cout << "\tTest 1 passed\n\n";
	
	//Test 2: File with two accounts
	cout << "\tTest 2: File with two valid accounts\n";
	am = AccountManager("loadAccount.txt");
	assert(123456 == am.accountList[0].accountNum);
	assert("Client1" == am.accountList[0].clientName);
	assert(1 == am.accountList[0].accountType);
	assert(100 == am.accountList[0].balance);
	assert(654321 == am.accountList[1].accountNum);
	assert("Client2" == am.accountList[1].clientName);
	assert(0 == am.accountList[1].accountType);
	assert(5000 == am.accountList[1].balance);
	cout << "\tTest 2 Passed\n\n";
	
	//Test 3: invalid file
	cout << "\tTest 3: invalid file\n";
	am = AccountManager("not-a-file.txt");
	assert(0 == am.accountList.size());
	cout << "\tTest 3 Passed\n\n";
}

//Save accounts test
void test_saveAccounts() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	cout << "saveAccounts() test\n";
	cout << "\tTest 1: saving account to valid file\n";
	AccountManager am("empty-file.txt");
	//Create account and save it to the file
	am.accountList.push_back(AccountManager::Account(123456, "Client Name", 0, 5000));
	am.saveAccounts();
	//Reinitialize/load newly saved stuff to confirm
	am = AccountManager("empty-file.txt");
	assert(1 == am.accountList.size());
	assert(123456 == am.accountList[0].accountNum);
	assert("Client Name" == am.accountList[0].clientName);
	assert(0 == am.accountList[0].accountType);
	assert(5000 == am.accountList[0].balance);
	cout << "\tTest 1 Passed\n\n";
}

//addAccount test
void test_addAccount() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	bool success;
	
	cout << "addAccount() testing\n";
	//Test 1: Normal case
	cout << "\tTest 1: Normal case, add client with valid fields\n";
	AccountManager am("empty-file.txt");
	success = am.addAccount(123456, "Client Name", 0, 5000);
	assert(true == success);
	assert(1 == am.accountList.size());
	assert(123456 == am.accountList[0].accountNum);
	assert("Client Name" == am.accountList[0].clientName);
	assert(0 == am.accountList[0].accountType);
	assert(5000 == am.accountList[0].balance);
	cout << "\tTest 1 passed\n\n";
	
	//Test 2: Invalid fields
	cout << "\tTest 2: invalid fields\n";
	//empty name
	cout << "\t\tTest 2.1: Empty client name\n";
	success = am.addAccount(12322, "", 0, 5000);
	assert(false == success);
	cout << "\t\tTest 2.1 passed\n";
	//Invalid type
	cout << "\t\tTest 2.2 invalid type\n";
	success = am.addAccount(12312, "Client", 52, 1000);
	assert(false == success);
	cout << "\t\tTest 2.2 passed\n";
	//Invalid balance
	cout << "\t\tTest 2.3 invalid balance\n";
	success = am.addAccount(12000, "Client", 1, -20);
	assert(false == success);
	cout << "\t\tTest 2.3 passed\n";
	cout << "\tTest 2 passed\n\n";
	
	//Test 3: account exists already
	cout << "\tTest 3: Account already exists\n";
	success = am.addAccount(123456, "Client Name", 0, 5000);
	assert(false == success);
	cout << "\tTest 3 passed\n\n";
}

//Test withdraw
void test_withdraw() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	AccountManager am("empty-file.txt");
	am.addAccount(123456, "Client Name", 0, 5000);
	bool success;
	
	cout << "withdraw() test\n";
	//Test one normal withdraw
	cout << "\tTest 1: valid withdrawals\n";
	success = am.withdraw(123456, 500);
	assert(true == success);
	assert(4500 == am.accountList[0].balance);
	success = am.withdraw(123456, 20);
	assert(true == success);
	assert(4480 == am.accountList[0].balance);
	success = am.withdraw(123456, 1000);
	assert(true == success);
	assert(3480 == am.accountList[0].balance);
	cout << "\tTest 1 passed\n\n";
	
	//Test 2 invalid withdrawAmount
	cout << "\tTest 2: invalid amount\n";
	//Negative amount
	cout << "\t\tTest 2.1: negative withdraw amount\n";
	success = am.withdraw(123456, -100);
	assert(false == success);
	assert(3480 == am.accountList[0].balance);
	cout << "\t\tTest 2.1 passed\n";
	//Overdraft
	cout << "\t\tTest 2.2: attempt to overdraft\n";
	success = am.withdraw(123456, 4000);
	assert(false == success);
	assert(3480 == am.accountList[0].balance);
	cout << "\t\tTest 2.2 passed\n";
	cout << "\tTest 2 passed\n\n";
	
	//Test 3: account does not exist
	cout << "\tTest 3: account does not exist\n";
	success = am.withdraw(00000, 20);
	assert(false == success);
	cout << "\tTest 3 passed\n\n";
}

//Test deposit()
void test_deposit() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	AccountManager am("empty-file.txt");
	am.addAccount(123456, "Client Name", 0, 5000);
	bool success;
	
	cout << "deposit() test\n";
	//Test 1 normal deposits
	cout << "\tTest 1: valid deposits\n";
	success = am.deposit(123456, 500);
	assert(true == success);
	assert(5500 == am.accountList[0].balance);
	success = am.deposit(123456, 20);
	assert(true == success);
	assert(5520 == am.accountList[0].balance);
	success = am.deposit(123456, 1000);
	assert(true == success);
	assert(6520 == am.accountList[0].balance);
	cout << "\tTest 1 passed\n\n";
	
	//Test 2 invalid depositAmount
	cout << "\tTest 2: invalid amount\n";
	//Negative amount
	cout << "\t\tTest 2.1: negative deposit amount\n";
	success = am.deposit(123456, -100);
	assert(false == success);
	assert(6520 == am.accountList[0].balance);
	cout << "\t\tTest 2.1 passed\n";
	//Overdraft
	cout << "\t\tTest 2.2: attempt to deposit more than $100,000\n";
	success = am.deposit(123456, 200000);
	assert(false == success);
	assert(6520 == am.accountList[0].balance);
	cout << "\t\tTest 2.2 passed\n";
	cout << "\tTest 2 passed\n\n";
	
	//Test 3: account does not exist
	cout << "\tTest 3: account does not exist\n";
	success = am.deposit(00000, 20);
	assert(false == success);
	cout << "\tTest 3 passed\n\n";
}

#endif

