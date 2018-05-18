/*
* Sloan Kiechel
* ssk0006
* ClientManager.cpp
*
* to compile:
* g++ -o ClientManager ClientManager.cpp
* NOTE: This is only for ClientManager testing. You must uncomment #define UNIT_TESTING below. 
* To compile/run the whole project, see System.cpp
* 
* c/Users/sloan/Dropbox/Spring_2018/Software_Construction/Project2
*
* Extra resources:
* http://www.cplusplus.com/forum/general/51349/ find/remove windows line ending /r from getline.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

//For testing. Comment out when not testing.
//#define UNIT_TESTING

//ClientManager class. Holds a list of clients and manages them.
class ClientManager {
	public:
		ClientManager(string filename); // Constructor
		ClientManager(); //Default constructor
		bool addClient(string nameIn, string addressIn, string employerIn, string ssIn, string incomeIn); //add Client
		bool editClient(string nameIn, string addressIn, string employerIn, string ssIn, string incomeIn);//edit Client
		bool displayClient(string nameIn); //Displays client
		bool isClient(string nameIn); //Checks if client exists
	private:
		//Struct to hold Client information.
		struct Client { 
			//constructor
			Client(string n, string a, string e, string ss, string i) 
					: name(n), address(a), employer(e), ssNum(ss), income(i) {};
			string name, address, employer;
			string  ssNum, income;
		};
		vector<Client> clientList;
		string clientFile; //File of clients
		void loadClients(); //Loads clients into clientList
		void saveClients(); //save clientList into client file
		static const string DEFAULT_FILE;
		/******************************************************************************/
		/****************************Test Functions************************************/
		/******************************************************************************/
		#ifdef UNIT_TESTING
		friend void test_loadClients();
		friend void test_saveClients();
		friend void test_addClient();
		friend void test_editClient();
		#endif
};

const string ClientManager::DEFAULT_FILE = "client-info.txt";

#ifdef UNIT_TESTING
//Definitions for testing functions
void test_loadClients();
void test_saveClients();
void test_addClient();
void test_editClient();
void test_isClient();

//For testing
int main () {
	test_loadClients();
	test_saveClients();
	test_addClient();
	test_editClient();
	test_isClient();
	
	//Test display
	ClientManager cm("loadClient.txt");
	cm.displayClient("Client1");
}
#endif

//Constructor. Takes file given and uses loadClients() to fill vector clientList.
ClientManager::ClientManager(string filename) {
	clientFile = filename;
	loadClients(); //Load clients
}

//Default constructor Set file to default file, load client list.
ClientManager::ClientManager() {
	clientFile = DEFAULT_FILE;
	loadClients(); //Load clients
}

//Load clients from file
void ClientManager::loadClients() {
	ifstream inStream;
	inStream.open((char*)clientFile.c_str());
	//if cannot find or open, display error
	if (inStream.fail()) {
		cout << "\tCannot open " << clientFile << endl;
	}
	else {
		//Retrieve client info
		string n, a, e, ss, i; //Name, address, employer, social secuirty, income
		//Puts data into placeholders from the file, then pushes this data into a new 
		//client in a client list.
		while (getline(inStream, n)) {
			getline(inStream, a); //Get address
			getline(inStream, e); //Get employer
			getline(inStream, ss); //Get social secuirty num
			getline(inStream, i); //Get income
			/*Windows adds an /r To the end of the file. I've never had it be an issue with getline() before,
			* but it was causing an issue this time, so this code corrects it incase a \r is read */
			if (n.at(n.size() -1) == '\r') {
				n.erase(n.size()-1);
			}
			if (a.at(a.size() -1) == '\r') {
				a.erase(a.size() -1);
			}
			if (e.at(e.size() -1) == '\r') {
				e.erase(e.size() -1);
			}
			if (ss.at(ss.size() -1) == '\r') {
				ss.erase(ss.size() -1);
			}
			if (i.at(i.size() -1) == '\r') {
				i.erase(i.size() -1);
			}
			//Adds the client to client list
			clientList.push_back(Client(n, a, e, ss, i));
		}
	}
	inStream.close(); //Close file
}

//Adds a client. Returns false if anything is empty or if the client already exsits.
bool ClientManager::addClient(string nameIn, string addressIn, string employerIn, string ssIn, string incomeIn) {
	//If any are empty, will not be added.
	if (nameIn == "" || addressIn == "" || employerIn == "" || ssIn == "" || incomeIn == "") {
		cout << "\tOne or more variables are empty. No client is added\n";
		return false;
	}
	//Search to be sure client doesn't exist
	for (int i = 0; i < clientList.size(); i ++) {
		//user already exists
		if (nameIn == clientList[i].name) {
			cout << "\tClient " << nameIn << " already exists. No client added\n";
			return false;
		}
	}
	//If everything is valid, add client.
	clientList.push_back(Client(nameIn, addressIn, employerIn, ssIn, incomeIn));
	saveClients();
	cout << "\tClient added and saved to client file\n";
	return true;
}

//Edits a client. Returns false if client doesn't exist.
//If fields are left blank, they are assumed as no change and the old value is used.
//Name is used to identify client, so it cannot be changed.
bool ClientManager::editClient(string nameIn, string addressIn, string employerIn, string ssIn, string incomeIn) {
	if (nameIn == "") {
		cout << "\tName cannot be empty!\n";
		return false;
	}
	//Search for client.
	for (int i = 0; i < clientList.size(); i ++) {
		//Client exists, edit information, return true
		if (nameIn == clientList[i].name) {
			if (addressIn != "") {
				clientList[i].address = addressIn;
			}
			if (employerIn != "") {
				clientList[i].employer = employerIn;
			}
			if (ssIn != "") {
				clientList[i].ssNum = ssIn;
			}
			if (incomeIn != "") {
				clientList[i].income = incomeIn;
			}
			saveClients();
			cout << "\tClient information updated\n";
			return true;
		}
	}
	//If gets here, client never found. Return false.
	cout << "\tClient " << nameIn << " not found. No changes made\n";
	return false;
}

//Saves clients to file
void ClientManager::saveClients() {
	ofstream outStream;
	outStream.open((char*)clientFile.c_str());
	//If fails, display error
	if (outStream.fail()) {
		cout << "\tCannot save client list to file " << clientFile << endl;
	}
	//Else, input client list to file.
	else {
		for (int i = 0; i < clientList.size(); i ++) {
			outStream << clientList[i].name << endl;
			outStream << clientList[i].address << endl;
			outStream << clientList[i].employer << endl;
			outStream << clientList[i].ssNum << endl;
			outStream << clientList[i].income << endl;
		}
	}
	outStream.close();
}

//Displays clients. Returns true if successfully found and displayed.
//False if client does not exist.
bool ClientManager::displayClient(string nameIn) {
	//If name is empty, return false.
	if (nameIn == "") {
		cout << "\tName cannot be empty!\n";
		return false;
	}
	//Search for client
	for (int i = 0; i < clientList.size(); i ++) {
		//client exists, display information
		if (nameIn == clientList[i].name) {
			cout << "\t" << nameIn << "'s Information: \n";
			cout << "\tAddress: " << clientList[i].address << endl;
			cout << "\tSocial Security Number: " << clientList[i].ssNum << endl;
			cout << "\tEmployer: " << clientList[i].employer << endl; 
			cout << "\tAnnual income: " << clientList[i].income << endl;
			return true;
		}
	}
	//If reach here, client never found.
	cout << "\tClient " << nameIn << " does not exist\n";
	return false;
}

//checks if client exists. True if client is in client list, false otherwise.
bool ClientManager::isClient(string nameIn) {
	//false if name is empty
	if (nameIn == "") {
		cout << "\tName cannot be empty!\n";
		return false;
	}
	//search for client
	for (int i = 0; i < clientList.size(); i++) {
		if (nameIn == clientList[i].name) {
			return true;
		}
	}
	//If reach here, did not find.
	return false;
}

/**************************************************************************************************/
/**********************************************TESTING*********************************************/
/**************************************************************************************************/
#ifdef UNIT_TESTING
//Load Clients test. 
void test_loadClients() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	cout << "loadClients() testing \n";
	//Test one: Empty file
	cout << "\tTest 1: Empty file\n";
	ClientManager cm("empty-file.txt");
	assert("empty-file.txt" == cm.clientFile);
	assert(0 == cm.clientList.size());
	cout << "\tTest 1 passed\n\n";
	
	//Test 2: File with two clients
	cout << "\tTest 2: Valid file with two valid clients\n";
	cm = ClientManager("loadClient.txt");
	assert("Client1" == cm.clientList[0].name);
	assert("Your mom's house" == cm.clientList[0].address);
	assert("Auburn" == cm.clientList[0].employer);
	assert("12345" == cm.clientList[0].ssNum);
	assert("70000" == cm.clientList[0].income);
	assert("Client2" == cm.clientList[1].name);
	assert("Meow St" == cm.clientList[1].address);
	assert("LCHS" == cm.clientList[1].employer);
	assert("12347" == cm.clientList[1].ssNum);
	assert("100000" == cm.clientList[1].income);
	cout << "\tTest 2 passed\n\n";
	
	//Test 3: invalid file
	cout << "\tTest 3: invalid file\n";
	cm = ClientManager("not-a-file.txt");
	assert(0 == cm.clientList.size());
	cout << "\tTest 3 Passed\n\n";
}

//Save clients test.
void test_saveClients() {
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	ClientManager cm("empty-file.txt");
	cout << "saveClients() test\n";
	cout << "\tTest 1: saving to valid file\n";
	//Create client and save it to the file.
	cm.clientList.push_back(ClientManager::Client("Name", "Address St", "Employer", "123-45-6789", "60000"));
	cm.saveClients();
	//Reinitialize/load newly saved stuff to confirm
	cm = ClientManager("empty-file.txt");
	assert(1 == cm.clientList.size());
	assert("Name" == cm.clientList[0].name);
	assert("Address St" == cm.clientList[0].address);
	assert("Employer" == cm.clientList[0].employer);
	assert("123-45-6789" == cm.clientList[0].ssNum);
	assert("60000" == cm.clientList[0].income);
	cout << "\tTest 1 Passed \n\n";
}

//addClient test
void test_addClient() {
	bool success;
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	cout << "addClient() Testing\n";
	//Test 1: Normal case
	cout << "\tTest 1: Normal case, add client with valid fields\n";
	ClientManager cm("empty-file.txt");
	success = cm.addClient("Name", "Address St", "Employer", "123-45-6789", "60000");
	assert(true == success);
	assert(1 == cm.clientList.size());
	assert("Name" == cm.clientList[0].name);
	assert("Address St" == cm.clientList[0].address);
	assert("Employer" == cm.clientList[0].employer);
	assert("123-45-6789" == cm.clientList[0].ssNum);
	assert("60000" == cm.clientList[0].income);
	cout << "\tTest 1 passed\n\n";
	
	//Test 2 Empty fields
	cout << "\tTest 2: Empty Fields\n";
	//Empty name test
	cout << "\t\tTest 2.1: Empty name\n";
	success = cm.addClient("", "Address St", "Employer", "123-45-6789", "60000");
	assert(false == success);
	cout << "\t\tTest2.1 passed\n";
	//Empty address test
	cout << "\t\tTest 2.2: Empty address\n";
	success = cm.addClient("Name", "", "Employer", "123-45-6789", "60000");
	assert(false == success);
	cout << "\t\tTest2.2 passed\n";
	//Empty Employer test
	cout << "\t\tTest 2.3: Empty employer\n";
	success = cm.addClient("Name", "Address St", "", "123-45-6789", "60000");
	assert(false == success);
	cout << "\t\tTest2.3 passed\n";
	//Empty social security number test
	cout << "\t\tTest 2.4: Empty social security number\n";
	success = cm.addClient("Name", "Address St", "Employer", "", "60000");
	assert(false == success);
	cout << "\t\tTest2.4 passed\n";
	//Empty income test
	cout << "\t\tTest 2.5: Empty income\n";
	success = cm.addClient("Name", "Address St", "Employer", "123-45-6789", "");
	assert(false == success);
	cout << "\t\tTest2.5 passed\n";
	cout << "\tTest 2 passed\n\n";
	
	//Test 3: Client already exists
	cout << "\tTest 3 client already exists\n";
	success = cm.addClient("Name", "Address St", "Employer", "123-45-6789", "");
	assert(false == success);
	assert(1 == cm.clientList.size());
	cout << "\tTest 3 passed\n\n";
}

//editClient test
void test_editClient() {
	bool success;
	//Reset empty-file.txt to be sure it is empty.
	ofstream outStream("empty-file.txt");
	outStream.close();
	
	cout << "edit client testing\n";
	ClientManager cm("empty-file.txt");
	//Test 1: Change all fields
	cout << "\tTest 1: Valid client, valid edits\n";
	cm.addClient("Name", "Address St", "Employer", "123-45-6789", "60000");
	//Test 1.1 edit everything
	cout << "\t\tTest 1.1: change all\n";
	success = cm.editClient("Name", "new drive", "new employer", "9876-54-321", "100000");
	assert(true == success);
	assert("new drive" == cm.clientList[0].address);
	assert("new employer" == cm.clientList[0].employer);
	assert("9876-54-321" == cm.clientList[0].ssNum);
	assert("100000" == cm.clientList[0].income);
	cout << "\t\tTest 1.1 passed\n";
	//Test 1.2 edit address only
	cout << "\t\tTest 1.2 edit address only\n";
	success = cm.editClient("Name", "newer rd", "", "", "");
	assert(true == success);
	assert("newer rd" == cm.clientList[0].address);
	assert("new employer" == cm.clientList[0].employer);
	assert("9876-54-321" == cm.clientList[0].ssNum);
	assert("100000" == cm.clientList[0].income);
	cout << "\t\tTest 1.2 passed\n";
	//Test 1.3 edit employer only
	cout << "\t\tTest 1.3 edit employer only\n";
	success = cm.editClient("Name", "", "newest employer", "", "");
	assert(true == success);
	assert("newer rd" == cm.clientList[0].address);
	assert("newest employer" == cm.clientList[0].employer);
	assert("9876-54-321" == cm.clientList[0].ssNum);
	assert("100000" == cm.clientList[0].income);
	cout << "\t\tTest 1.3 passed\n";
	//Test 1.4 edit SS num only
	cout << "\t\tTest 1.4 edit SS number only\n";
	success = cm.editClient("Name", "", "", "000-00-0000", "");
	assert(true == success);
	assert("newer rd" == cm.clientList[0].address);
	assert("newest employer" == cm.clientList[0].employer);
	assert("000-00-0000" == cm.clientList[0].ssNum);
	assert("100000" == cm.clientList[0].income);
	cout << "\t\tTest 1.4 passed\n";
	//Test 1.5 edit income only
	cout << "\t\tTest 1.5 edit income only\n";
	success = cm.editClient("Name", "", "", "", "5");
	assert(true == success);
	assert("newer rd" == cm.clientList[0].address);
	assert("newest employer" == cm.clientList[0].employer);
	assert("000-00-0000" == cm.clientList[0].ssNum);
	assert("5" == cm.clientList[0].income);
	cout << "\t\tTest 1.5 passed\n";
	//Test 1.6 Edit nothing
	cout << "\t\tTest 1.6 edit nothing\n";
	success = cm.editClient("Name", "", "", "", "");
	assert(true == success);
	assert("newer rd" == cm.clientList[0].address);
	assert("newest employer" == cm.clientList[0].employer);
	assert("000-00-0000" == cm.clientList[0].ssNum);
	assert("5" == cm.clientList[0].income);
	cout << "\t\tTest 1.6 passed\n";
	cout << "\tTest 1 passed\n\n";
	
	//Test 2: Invalid uses
	cout << "\tTest 2: Invalid input\n";
	//Test 2.1 empty name
	cout << "\t\tTest 2.1: empty name\n";
	success = cm.editClient("", "new drive", "new employer", "9876-54-123", "100000");
	assert(false == success);
	cout << "\t\tTest 2.1 passed\n";
	//Test 2.2 client does not exist
	cout << "\t\tTest 2.2 invalid client\n";
	success = cm.editClient("Not a client", "new drive", "new employer", "9876-54-123", "100000");
	assert(false == success);
	cout << "\t\tTest 2.2 Passed\n";
	cout << "\tTest 2 passed\n\n";
}

//Test isClient()
void test_isClient() {
	cout << "isClient Testing\n";
	//Test 1 valid clients
	cout << "\tTest 1: Valid client\n";
	ClientManager cm("loadClient.txt");
	assert(true == cm.isClient("Client1"));
	assert(true == cm.isClient("Client2"));
	cout << "\tTest 1 passed\n\n";
	//Test 2 empty name
	cout << "\tTest 2: empty name\n";
	assert(false == cm.isClient(""));
	cout << "\tTest 2 passed\n\n";
	//Test 3 not a client
	cout << "\tTest 3: not a client\n";
	assert(false == cm.isClient("Not a client"));
	cout << "\tTest 3 passed\n\n";
}

#endif