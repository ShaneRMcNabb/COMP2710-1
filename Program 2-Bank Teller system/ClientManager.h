/*
* Sloan Kiechel
* ssk0006
* ClientManager.h
* ClientManager header to link ClientManager class
*/

#include <string>
#include <vector>
using namespace std;

#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

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
};

//const string ClientManager::DEFAULT_FILE = "client-info.txt";

#endif