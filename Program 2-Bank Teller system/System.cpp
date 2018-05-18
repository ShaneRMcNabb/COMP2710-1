/*
* Sloan Kiechel
* ssk0006
* System.cpp
*
* to compile:
* g++ EmployeeManager.cpp ClientManager.cpp AccountManager.cpp System.cpp -o system
*
* This is the main class. Run this to start the banking system. 
*
* c/Users/sloan/Dropbox/Spring_2018/Software_Construction/Project2
*
* Extra resource(s):
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "EmployeeManager.h" //employee manager class
#include "ClientManager.h" //client manager class
#include "AccountManager.h" //account manager class
using namespace std;

//system class. Uses the employee, client, and account managers to run a bank system.
class System {
	public:
		System(); //Constructor
		void idleState(); //Idle screen
		void branchScreen(); //Branch Staff menu
		void sysAdminScreen(); //System admin menu
		void logout();
		void clientManagement(); //Client management menu
		void manageAccount(int accountNumber); //Withdraw/deposit from account
		void changePassword();
	private:
		EmployeeManager employeeManager;
		ClientManager clientManager;
		AccountManager accountManager;
		bool idle;
		void verifyInput(int numOfChoices); //Verify that user inputs a valid menu number
		int menuChoice; //User's choice from menu
		string currentUser; //Sets current user
};

//This main runs the full banking system.
int main() {
	System system;
}

//Constructor. Starts the idle screen.
System::System() {
	menuChoice = 0;
	currentUser = "";
	idle = true;
	idleState();
}

//Verifies menu input
void System::verifyInput(int numOfChoices){ 
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail() || menuChoice < 1 || menuChoice > numOfChoices) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please input number from 1 to " << numOfChoices << endl;
		cout << "\nPlease choose an action: ";
		cin >> menuChoice;
	}

}

//The idle state of the system. Asks for login information, and allows user to exit.
void System::idleState() {
	while (idle) {
		string username, password; //Placeholders when users attempt to login
		cout << "\n===========================================================\n";
		cout << "|\tWelcome to the Auburn Branch of Tiger Bank!\t|\n";
		cout << "===========================================================\n";
		cout << "1) Login\n2) Quit\n";
		cout << "\tPlease choose an option: ";
		cin >> menuChoice;
		verifyInput(2); //Makes sure input is valid
		//Login
		if (menuChoice == 1) {
			cout << "\n===========================================================\n";
			cout << "|\tLogin to Access the Teller Terminal System\t|\n";
			cout << "===========================================================\n";
			cout << "User name: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			if (username == "" || password == "") {
				cout << "Username and password cannot be blank\n\n";
			}
			else if (employeeManager.verifyLogin(username, password)) {
				currentUser = username;
				idle = false;
			}
			else {
				cout << "Username or password is incorrect\n\n";
			}
		}
		//Quit
		else {
			cout << "\nAre you sure you want to quit?\n";
			cout << "1) Confirm\n";
			cout << "2) Cancel\n";
			cout << "\tPlease choose an option: ";
			cin >> menuChoice;
			verifyInput(2);
			//Log out
			if (menuChoice == 1) {
				idle = false;
				exit(1);
			}
		}
	}
	//Login successful. Move to either branch or admin screen.
	if (employeeManager.isAdmin(currentUser)) {
		sysAdminScreen();
	}
	else {
		branchScreen();
	}
}

//System admin screen. Called when a system admin logs in.
void System::sysAdminScreen() {
	//turn idle back to true when logging off
	string name, password;
	int role;
	while (!idle) {
		//Display menu and get input
		cout << "\n===========================================================\n";
		cout << "|\tWelcome to the Auburn Branch of Tiger Bank!\t|\n";
		cout << "===========================================================\n";
		cout << "1) Client and Account Management\n2) Add a branch staff member\n";
		cout << "3) Delete a branch staff member\n4) Display branch staff\n";
		cout << "5) Change password\n6) Log out\n";
		cout << "\tPlease choose an option: ";
		cin >> menuChoice;
		verifyInput(6);
		//Process input
		switch (menuChoice) {
			//Client and Account management
			case 1:
				clientManagement();
				break;
			//Add branch staff member	
			case 2: 
				cout << "\nEnter username and password of new staff\n";
				cout << "Username: ";
				cin.ignore(1000, '\n');
				cin >> name;
				cout << "Password: ";
				cin >> password;
				cout << "Role (1 = Administrator, 2 = Branch staff): ";
				cin >> role;
				if (role == 1) {
					employeeManager.addEmployee(name, password, true);
				}
				else if (role == 2) {
					employeeManager.addEmployee(name, password, false);
				}
				else { 
					cout << "Invalid role assignment. No employee added\n";
				}
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Delete branch staff member
			case 3: 
				cout << "\nDelete what user: ";
				cin.ignore(1000, '\n');
				cin >> name;
				if (name != currentUser) {
					cout << "Are you sure you want to delete " << name << "?\n";
					cout << "1) Confirm\n";
					cout << "2) Cancel\n";
					cout << "\tPlease choose an option: ";
					cin >> menuChoice;
					verifyInput(2);
					if (menuChoice == 1) {
						employeeManager.deleteEmployee(name);
					}
					else {
						cout << "Delete canceled. No employee was deleted\n";
					}
				}
				else {
					cout << "You cannot delete yourself!\n";
				}
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Display staff	
			case 4:
				employeeManager.displayEmployees();
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Change password
			case 5:
				changePassword();
				break;
			//Log out
			case 6:
				cout << "\nAre you sure you want to log out?\n";
				cout << "1) Confirm\n";
				cout << "2) Cancel\n";
				cout << "\tPlease choose an option: ";
				cin >> menuChoice;
				verifyInput(2);
				//Log out
				if (menuChoice == 1) {
					currentUser = "";
					idle = true;
				}
				break;
			//Should never default because of verifyInput().
			default:
				cout << "Error. Cannot detect valid input\n";
		}
	}
	//If code reaches here, user has logged out. system returns to idle state.
	idleState();
}

//Branch staff menu. Displays when a branch staff member logs in.
void System::branchScreen() {
	//Idle turns to true when logging off.
	while (!idle) {
		//Display menu and get input
		cout << "\n===========================================================\n";
		cout << "|\tWelcome to the Auburn Branch of Tiger Bank!\t|\n";
		cout << "===========================================================\n";
		cout << "1) Client and Account Management\n2) Change password\n3) Log out\n";
		cout << "\tPlease choose an option: ";
		cin >> menuChoice;
		verifyInput(3);
		//Process input
		switch (menuChoice) {
			//Client and account management
			case 1: 
				clientManagement();
				break;
			//Change password
			case 2:
				changePassword();
				break;
			//Logout
			case 3:
				cout << "\nAre you sure you want to log out?\n";
				cout << "1) Confirm\n";
				cout << "2) Cancel\n";
				cout << "\tPlease choose an option: ";
				cin >> menuChoice;
				verifyInput(2);
				//Log out
				if (menuChoice == 1) {
					currentUser = "";
					idle = true;
				}
				break;
		}
	}
	//If code reaches here, user has logged out. system returns to idle state.
	idleState();
}

//Client management menu. Accessible by both system admins and branch staff.
void System::clientManagement() {
	bool clientManage = true; //True while user wants to manage clients/accounts
	string name, address, employer, ssNum, income;
	int accountNum, accountType, balance;
	while (clientManage) {
		cout << "\n================================================================\n";
		cout << "|\tTeller Terminal System - Client and Account Management\t|\n";
		cout << "================================================================\n";
		cout << "1) Add a client\n2) Add an account\n3) Edit Client Information\n";
		cout << "4) Manage an account\n5) Return to previous menu\n";
		cout << "\tPlease choose an option: ";
		cin >> menuChoice;
		verifyInput(5);
		switch (menuChoice) {
			//Add a client
			case 1: 
				//Get input from user
				cout << "\nA new client will be added:\n";
				cout << "Client name: ";
				cin.ignore(1000, '\n');
				getline(cin, name);
				cout << "Address: ";
				getline(cin, address);
				cout << "Employer: ";
				getline(cin, employer);
				cout << "Social security number: ";
				cin >> ssNum;
				cout << "Annual income: ";
				cin >> income;
				//Add client
				clientManager.addClient(name, address, employer, ssNum, income);
				//Prompt to continue
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Add an account
			case 2: 
				//Get client
				cout << "\nChoose a client: ";
				cin.ignore(1000, '\n');
				getline(cin, name);
				//If client exists, get account information to add
				if (clientManager.isClient(name)) {
					cout << "A new account will be created for " << name << "...\n";
					cout << "Account number: ";
					cin >> accountNum;
					cout << "Account Type (0 for checkings, 1 for savings): ";
					cin >> accountType;
					cout << "Balance: ";
					cin >> balance;
					//Add the account
					accountManager.addAccount(accountNum, name, accountType, balance);
				}
				else { 
					cout << name << "does not exist. No account added\n";
				}
				//Prompt to continue
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Edit client info
			case 3: 
				cout << "\nChoose a client: ";
				cin.ignore(1000, '\n');
				getline(cin, name);
				//If client does not exist, display error
				if (!clientManager.isClient(name)) {
					cout << "Client " << name << " does not exist\n";
				}
				//Client does exist. Confirm update, then get input.
				else {
					//Display client
					clientManager.displayClient(name);
					//Prompt for confirmation
					cout <<"Client " << name << "'s information will be updated\n";
					cout << "1) Confirm\n";
					cout << "2) Cancel\n";
					cout << "\tPlease choose an option: ";
					cin >> menuChoice;
					verifyInput(2);
					//Prompt for changes
					if (menuChoice == 1) {
						cout << "Address: ";
						cin.ignore(1000, '\n');
						getline(cin, address);
						cout << "Employer: ";
						getline(cin, employer);
						cout << "Social Security Number: ";
						cin >> ssNum;
						cout << "Annual income: ";
						cin >> income;
						clientManager.editClient(name, address, employer, ssNum, income);
					}
					else {
						cout << "No information changed\n";
					}
				}
				//Prompt to continue
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Manage an account
			case 4:
				cout << "\nWhich account will be managed: ";
				cin >> accountNum;
				if (accountManager.isAccount(accountNum)) {
					manageAccount(accountNum);
				}
				else {
					cout << "Account " << accountNum << " does not exist\n";
				}
				//Prompt to continue
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Return to previous screen
			case 5: 
				cout << "\nAre you sure you want to return to the previous menu?\n";
				cout << "1) Confirm\n";
				cout << "2) Cancel\n";
				cout << "\tPlease choose an option: ";
				cin >> menuChoice;
				verifyInput(2);
				if (menuChoice == 1) {
					clientManage = false;
					cout << "\nExiting  Client and Account Management Menu...\n";
				}
				break;
			//should never reach default.
			default:
				cout << "Error. Cannot detect valid input\n";
		}
	}
}

//withdraw/deposit money into an account
void System::manageAccount(int accountNumber) {
	bool accountMenu = true;
	int depositAmount, withdrawAmount;
	while (accountMenu) {
		cout << endl;
		accountManager.displayAccount(accountNumber);
		cout << "1) Deposit\n2) Withdraw\n3) Cancel\n";
		cout << "\tPlease choose an option: ";
		cin >> menuChoice;
		verifyInput(3);
		switch (menuChoice) {
			//Deposit
			case 1:
				cout << "Deposit amount: ";
				cin >> depositAmount;
				accountManager.deposit(accountNumber, depositAmount);
				//Prompt to continue
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			//Withdraw
			case 2: 
				cout << "Withdraw amount: ";
				cin >> withdrawAmount;
				accountManager.withdraw(accountNumber, withdrawAmount);
				//Prompt to continue
				cout << "Press any key to continue... ";
				cin.ignore().get(); //Pause Command for Linux Terminal
				break;
			case 3: 
				cout << "\nAre you sure you want to return to the previous menu?\n";
				cout << "1) Confirm\n";
				cout << "2) Cancel\n";
				cout << "\tPlease choose an option: ";
				cin >> menuChoice;
				verifyInput(2);
				if (menuChoice == 1) {
					accountMenu = false;
					cout << "\nExiting Account Management Menu...\n";
				}
				break;
		}
	}
}

//Changes password of user. Verifies current password firs, then prompts for new password.
void System::changePassword() {
	string currentPass, newPass1, newPass2; //Placeholders for comparison
	cout << "\nEnter your current password: ";
	cin.ignore(1000, '\n');
	cin >> currentPass;
	//If current pass is correct, prompt for new password
	if (employeeManager.verifyLogin(currentUser, currentPass)) {
		cout << "Enter your new password: ";
		cin >> newPass1;
		cout << "Confirm your new password: ";
		cin >> newPass2;
		//verify passwords match
		if (newPass1 == newPass2) {
			if (employeeManager.changePassword(currentUser, newPass1)) {
				cout << "Password successfully updated!\n";
			}
			else {
				cout << "No change made\n";
			}
		}
	}
	else {
		cout << "Incorrect password. Returning to main menu...\n";
	}
	cout << "Press any key to continue... ";
	cin.ignore().get(); //Pause Command for Linux Terminal
}