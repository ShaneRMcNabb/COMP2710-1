/*
* Sloan Kiechel
* ssk0006
* EmployeeManager.cpp
*
* to compile:
* g++ -o EmployeeManager EmployeeManager.cpp
* NOTE: This is only for EmployeeManager testing. You must uncomment #define UNIT_TESTING below. 
* To compile/run the whole project, see System.cpp
* 
* c/Users/sloan/Dropbox/Spring_2018/Software_Construction/Project2
*
* Extra resource(s):
* http://www.cplusplus.com/forum/beginner/235586/ shortened/fixed code in loadEmployees with online help.
* http://www.cplusplus.com/reference/vector/vector/ More vector functions not taught in class.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

//For testing. Comment out when not testing.
//#define UNIT_TESTING

//EmployeeManager class. Holds a list of employees and manages them.
class EmployeeManager {
	public:
		EmployeeManager(string filename); // Constructor
		EmployeeManager(); //Default constructor
		bool verifyLogin(string user, string pass); //Verifies login information
		bool changePassword(string user, string newPass); //change password
		bool isAdmin(string username); //Verify if user is admin
		bool addEmployee(string user, string pass, bool isAdmin); //add Employee
		bool deleteEmployee(string user); //Delete employee
		void displayEmployees(); //Displays employee list. Might overload << instead.
	private:
		//Struct to hold employee information.
		struct Employee { 
			//constructor
			Employee(string u, string p, bool a) : username(u), password(p), admin(a) {};
			string username;
			string password;
			bool admin; //True if admin, false if not
		};
		vector<Employee> employeeList;
		string employeeFile; //File of employees
		void loadEmployees(); //Loads employees into employeeList
		void saveEmployees(); //save employeeList into employee file
		static const string DEFAULT_FILE;
		/******************************************************************************/
		/****************************Test Functions************************************/
		/******************************************************************************/
		#ifdef UNIT_TESTING
		friend void test_loadEmployees();
		friend void test_saveEmployees();
		friend void test_addEmployee();
		friend void test_isAdmin();
		friend void test_verifyLogin();
		friend void test_changePassword();
		friend void test_deleteEmployee();
		#endif
};

#ifdef UNIT_TESTING
//Definitions for the testing functions.
void test_loadEmployees();
void test_saveEmployees();
void test_addEmployee();
void test_isAdmin();
void test_verifyLogin();
void test_changePassword();
void test_deleteEmployee();

//Used for testing.
int main() {
	test_loadEmployees();
	test_saveEmployees();
	test_addEmployee();
	test_isAdmin();
	test_verifyLogin();
	test_changePassword();
	test_deleteEmployee();
	//displayTest
	EmployeeManager testEM("loadTest.txt");
	testEM.displayEmployees();
}
#endif

//Initialize default file
const string EmployeeManager::DEFAULT_FILE = "staff.txt";

//Constructor. Takes the file given and uses loadEmployees() to fill the vector employeeList.
EmployeeManager::EmployeeManager(string filename) {
	employeeFile = filename;
	loadEmployees(); //Load employees
}

//Default constructor.
//Set file to default file. Load employee list. If no employees,
//create default admin with password 0000.
EmployeeManager::EmployeeManager() {
	employeeFile = DEFAULT_FILE;
	loadEmployees(); //Load employees
}

//Verifies login is correct. Returns false if incorrect, true if correct
//Note, no output is placed here because System will handle the output when needed.
bool EmployeeManager::verifyLogin(string user, string pass) {
	//Search for username
	for (int i = 0; i < employeeList.size(); i++) {
		//User exists
		if (user == employeeList[i].username) {
			//If pass is the password, return true. If they don't match, return false.
			return (pass == employeeList[i].password);
		}
	}
	//If the function reaches this point, the employee was never found.
	//Do not want to output "employee doesn't exist" because this will make brute-forcing
	//in much easier, since they will know if the username is valid. thus, just return false
	//and allow System class to handle the output.
	return false;
}

//Changes user Password
//Note: System uses I/O to verify the user has the correct login. Then this function is called
//To change to the new password.
bool EmployeeManager::changePassword(string user, string newPass) {
	//Verify newPass is not empty.
	if (newPass == "") {
		cout << "\tPassword cannot be empty\n";
		return false;
	}
	//Verify user is valid.
	for (int i = 0; i < employeeList.size(); i++) {
		//User exists
		if (user == employeeList[i].username) {
			//If pass is the password, return false (can't change to current).
			if (newPass == employeeList[i].password) {
				cout << "\tNew password cannot be the same as current\n";
				return false;
			}
			//Password is different and already determined as valid. Change successful.
			else {
				employeeList[i].password = newPass;
				//Update employee file
				saveEmployees();
				return true;
			}
		}
	}
	//If the function reaches this, user did not exist. Return false.
	cout << "\tError, user does not exist. Report to developer\n";
	return false;
}

//Returns true if user is an admin, false if not an admin. 
//Displays error message and false if employee does not exist.
bool EmployeeManager::isAdmin(string user){
	//Search and be sure user exists.
	for (int i = 0; i < employeeList.size(); i++) {
		//User already exists
		if (user == employeeList[i].username) {
			return employeeList[i].admin;
		}
	}
	//If function reaches here, the user was not found.
	cout << "\tThe user " << user << " does not exist\n";
	return false;
}

//Loads employees from employeeFile. If no employees, create default admin with password 0000.
//If fails to open, display error message.
void EmployeeManager::loadEmployees() {
	ifstream inStream;
	inStream.open((char*)employeeFile.c_str());
	//If cannot find or open, display error.
	if (inStream.fail()) {
		cout << "\tCannot open " << employeeFile << endl;
	}
	else {
		//Retrieve employee info
		//Note: Info is stored as username on the first line, password on the next, and then
		//0 or 1 to signify if the user is an admin or not.
		int a; //Admin
		string u, p; //Username/password
		//This statement puts the username, password, and admin status into the placeholder variables.
		//It also checks that it is true/false, or rather, it has not yet reached the end of file.
		while (inStream >> u >> p >> a) {
			employeeList.push_back(Employee(u, p, a));
		}
	}
	inStream.close(); //Close file
	//If nothing in file, create default admin
	if (employeeList.empty()) {
		employeeList.push_back(Employee("admin", "0000", 1));
	}
}

//Saves employees to file
void EmployeeManager::saveEmployees() {
	ofstream outStream;
	outStream.open((char*)employeeFile.c_str());
	//If fails, display error
	if (outStream.fail()) {
		cout << "Cannot save employee list to file " << employeeFile << endl;
	}
	//Else, input employee list to file.
	else {
		for (int i = 0; i < employeeList.size(); i ++) {
			outStream << employeeList[i].username << endl;
			outStream << employeeList[i].password << endl;
			//Save admin status as 0 or 1. 0 = false. 1 = true
			if (employeeList[i].admin) {
				outStream << "1\n";
			}
			else {
				outStream << "0\n";
			}
		}
	}
	outStream.close();
}

//Adds an employee. Returns false and error message if u, p are empty or if user already exists.
//Used bool so System can also error check if so desired.
bool EmployeeManager::addEmployee(string user, string pass, bool isAdmin) {
	//If u or p is empty, return an error message, and return false.
	if (user == "" || pass == "") {
		cout << "Username or password not valid. User not added.\n";
		return false;
	}
	//Search and be sure user doesn't already exist.
	for (int i = 0; i < employeeList.size(); i++) {
		//User already exists
		if (user == employeeList[i].username) {
			cout << "User " << user << " already exists. No user added\n";
			return false;
		}
	}
	//If everything else is valid, add the user and save user list.
	employeeList.push_back(Employee(user, pass, isAdmin));
	saveEmployees();
	cout << "Employee added and saved to staff file\n";
	return true;
}

//Deletes an employee. System first asks for the user to delete, and asks for confirmation.
//If user confirms, then this function is called. Returns true if successful, false if not.
//Note: System must ensure that the user being deleted is not the current user.
bool EmployeeManager::deleteEmployee(string user) {
	//Ensure user is not empty.
	if (user == "") {
		cout << "\tUsername cannot be empty\n";
		return false;
	}
	//Search if user exists.
	for (int i = 0; i < employeeList.size(); i++) {
		//User exists, delete user.
		if (user == employeeList[i].username) {
			//Erase function deletes element and shifts list. Not super efficient, but fine for small scale.
			employeeList.erase(employeeList.begin() + i);
			saveEmployees(); //Save changes to file
			cout << "\tUser " << user << " was successfully deleted.\n";
			return true;
		}
	}
	//If reach here, user does not exist.
	cout << "\tThe user " << user << " does not exist. No user deleted\n";
	return false;
}

//Displays employees
//Since admin is automatically made, employeelist will always have a size of atleast 1.
void EmployeeManager::displayEmployees() {
	cout << "\tThere are " << employeeList.size() << " users in the system:\n";
	for (int i = 0; i < employeeList.size(); i++) {
		cout << "\t" << i + 1 << ". Username: " << employeeList[i].username << "\tRole: ";
		if (employeeList[i].admin) {
			cout << "System Administrator\n";
		}
		else {
			cout << "Branch Staff\n";
		}
	}
}

/**************************************************************************************************/
/**********************************************TESTING*********************************************/
/**************************************************************************************************/
#ifdef UNIT_TESTING
//Load employees test. Also tests constructors since they call loadEmployees automatically.
void test_loadEmployees() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	cout << "loadEmployees() testing.\n";
	//Test one: empty file. Should create default admin.
	cout << "\tTest 1: file exists but is empty\n";
	EmployeeManager em("empty-file.txt");
	assert("empty-file.txt" == em.employeeFile);
	assert("admin" == em.employeeList[0].username);
	assert("0000" == em.employeeList[0].password);
	assert(true == em.employeeList[0].admin);
	cout << "\tTest 1 Passed\n\n";
	
	//Test two: File with Two employees: one admin, one not.
	cout << "\tTest 2: loadTest.txt file, two employess, one admin, one not\n";
	em = EmployeeManager("loadTest.txt");
	assert("loadTest.txt" == em.employeeFile);
	assert("testAdmin" == em.employeeList[0].username);
	assert("adminPass" == em.employeeList[0].password);
	assert(true == em.employeeList[0].admin);
	assert("testUser" == em.employeeList[1].username);
	assert("userPass" == em.employeeList[1].password);
	assert(false == em.employeeList[1].admin);
	cout << "\tTest 2 Passed\n\n";
	
	//Test three: file doesn't exist
	cout << "\tTest 3: file doesn't exist. Should declare error message, still create admin.\n";
	em = EmployeeManager("not-a-file.txt");
	assert("not-a-file.txt" == em.employeeFile);
	assert("admin" == em.employeeList[0].username);
	assert("0000" == em.employeeList[0].password);
	assert(true == em.employeeList[0].admin);
	cout << "\tTest 3 Passed\n\n";
}

//Test saveEmployees()
void test_saveEmployees() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	EmployeeManager em("empty-file.txt");
	
	cout << "saveEmployees() Testing.\n";
	//Test 1: Normal usage. File already exists.
	cout << "\tTest 1: Saving to a file that already exists\n";
	//File is empty, so default admin should be in there.
	assert("admin" == em.employeeList[0].username);
	assert("0000" == em.employeeList[0].password);
	assert(true == em.employeeList[0].admin);
	//Add an extra employee
	em.employeeList.push_back(EmployeeManager::Employee("testUser", "testPass", false));
	//Save employee list
	em.saveEmployees();
	//Re-open/initilaize. Should load new new employee too.
	em = EmployeeManager("empty-file.txt");
	assert(2 == em.employeeList.size());
	assert("admin" == em.employeeList[0].username);
	assert("0000" == em.employeeList[0].password);
	assert(true == em.employeeList[0].admin);
	assert("testUser" == em.employeeList[1].username);
	assert("testPass" == em.employeeList[1].password);
	assert(false == em.employeeList[1].admin);
	cout << "\tTest 1: passed\n\n";
}

//Test addEmployee()
void test_addEmployee() {
	bool success;
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	cout << "addEmployee() Testing\n";
	//Test 1: Normal case
	cout << "\tTest 1: Normal case, add normal employee with valid fields\n";
	EmployeeManager em("empty-file.txt");
	//Admin is automatically added because the file is empty. Next user is 2nd, not first user.
	success = em.addEmployee("testUser", "testPass", false);
	assert(true == success);
	assert(2 == em.employeeList.size());
	assert("admin" == em.employeeList[0].username);
	assert("0000" == em.employeeList[0].password);
	assert(true == em.employeeList[0].admin);
	assert("testUser" == em.employeeList[1].username);
	assert("testPass" == em.employeeList[1].password);
	assert(false == em.employeeList[1].admin);
	cout << "\tTest 1: passed\n\n";
	
	//Test 2: Empty password.
	cout << "\tTest 2: Password empty\n";
	success = em.addEmployee("test2", "", false);
	assert(false == success);
	assert(2 == em.employeeList.size());
	cout << "\tTest 2: passed\n\n";
	
	//Test 3: empty username
	cout << "\tTest 3: username empty\n";
	success = em.addEmployee("", "test2", false);
	assert(false == success);
	assert(2 == em.employeeList.size());
	cout << "\tTest 3: passed\n\n";
	
	//Test 4: User already exists
	cout << "\tTest 4: user already exists\n";
	success = em.addEmployee("testUser", "testPass", false);
	assert(false == success);
	assert(2 == em.employeeList.size());
	cout << "\tTest 4: passed\n\n";
}

//Test isAdmin()
void test_isAdmin() {
	cout << "isAdmin() testing\n";
	//Test 1: Employee that is an admin
	cout << "\tTest 1: Employee is an admin\n";
	EmployeeManager em("loadTest.txt");
	assert(true == em.isAdmin("testAdmin"));
	cout << "\tTest 1 Passed\n\n";
	//Test 2: Employee not an admin
	cout << "\tTest 2: Employee is not an admin\n";
	assert(false == em.isAdmin("testUser"));
	cout << "\tTest 2 Passed\n\n";
	//Test 3: Employee does not exist.
	cout << "\tTest 3: Employee does not exist\n";
	assert(false == em.isAdmin("bob"));
	cout << "\tTest 3 Passed\n\n";
}

//test verifyLogin()
void test_verifyLogin() {
	EmployeeManager em("loadTest.txt");
	cout << "verifyLogin() testing\n";
	//Test 1: Login is valid
	cout << "\tTest 1: valid login\n";
	assert(true == em.verifyLogin("testAdmin", "adminPass"));
	cout << "\tTest 1 Passed\n\n";
	//Test 2: Login not valid
	cout << "\tTest 2: Invalid login\n";
	assert(false == em.verifyLogin("employee", "notapassword"));
	cout << "\tTest 2 Passed\n\n";
	//Test 3: Employee does not exist.
	cout << "\tTest 3: Employee does not exist\n";
	assert(false == em.verifyLogin("bob", "pass"));
	cout << "\tTest 3 Passed\n\n";
}

//test changePassword()
void test_changePassword() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	//Add employees that we will change
	EmployeeManager em("empty-file.txt");
	em.addEmployee("employee", "pass", false);
	em.addEmployee("bob", "woof", false);
	
	cout << "changePassword() testing\n";
	//Test 1: Use valid usernames/passwords. 
	cout << "\tTest 1: Using valid usernames/new passwords\n";
	assert(true == em.changePassword("admin", "meow"));
	assert(true == em.changePassword("employee", "meow2"));
	assert(true == em.changePassword("bob", "meow3"));
	//reload list to check it saved
	em.employeeList.clear();
	em.loadEmployees();
	assert("meow" == em.employeeList[0].password);
	assert("meow2" == em.employeeList[1].password);
	assert("meow3" == em.employeeList[2].password);
	cout << "\tTest 1 passed\n\n";
	//Test 2: Empty password
	cout << "\tTest 2: Invalid (empty) password\n"; 
	assert(false == em.changePassword("admin", ""));
	cout << "\tTest 2 passed\n\n";
	//Test 3: New pass same as old pass.
	cout << "\tTest 3: New password same as old\n";
	assert(false == em.changePassword("admin", "meow"));
	cout << "\tTest 3 passed\n\n";
	//Test 4: User does not exist
	cout << "\tTest 4: User does not exist\n";
	assert(false == em.changePassword("notReal", "fake"));
	cout << "\tTest 4 Passed\n\n";
}

//Test deleteEmployee()
void test_deleteEmployee() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	//Setting up
	EmployeeManager em("empty-file.txt");
	em.addEmployee("admin2", "meow", 1);
	em.addEmployee("normie", "meow", 0);
	em.addEmployee("rando", "meow", 0);
	
	cout << "deleteEmployee() testing\n";
	//Test 1: Normal usage. Delete valid user.
	cout << "\tTest 1: Normal usage, delete valid user\n";
	assert(true == em.deleteEmployee("normie"));
	assert(3 == em.employeeList.size()); //Our 2 users + the default.
	assert(true == em.deleteEmployee("admin2"));
	assert(2 == em.employeeList.size());
	//Ensure everything shifted fine.
	assert("admin" == em.employeeList[0].username);
	assert("rando" == em.employeeList[1].username);
	cout << "\tTest 1 passed.\n\n";
	//Test 2: Empty username
	cout << "\tTest 2: empty username\n";
	assert(false == em.deleteEmployee(""));
	cout << "\tTest 2 passed.\n\n";
	//Test 3: User does not exist.
	cout << "\tTest 3: user does not exist\n";
	assert(false == em.deleteEmployee("woof"));
	cout << "\tTest 3 passed.\n\n";
}

#endif