/*
* Sloan Kiechel
* ssk0006
* EmployeeManager.h
* EmployeeManager header to link EmployeeManager class
*/

#include <string>
#include <vector>
using namespace std;

#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

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
};

//const string EmployeeManager::DEFAULT_FILE = "staff.txt";

#endif