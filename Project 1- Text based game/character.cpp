/*
* Sloan Kiechel
* ssk0006
* character.cpp
*
* to compile:
* g++ -o character character.cpp
* 
* Note: That only compiles character.cpp. For the entire game, see "game.cpp"
* Also Note: If trying to commpile this seperately with the above, you have to uncomment main().
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <iomanip> 
using namespace std;

//Character Class
//Holds all player info (name, time, intelligence, money)
class Character {
	public:
		Character(); //Constructor
		Character(string charName); //Constructor that already has player name
		//Constructor, all stats inputed
		Character(string charName, int timeIn, int intellIn, double moneyIn);
		string name; //Name of player
		int time; //time remaining
		int intelligence; //intelligence of a character
		double money; //Money character has
		int steps; //length of hallway
		void displayStats(); //Displays character stats
	private:
		//Default values
		static const int DEFAULT_TIME = 25;
		static const int DEFAULT_INTELLIGENCE = 15;
		static const double DEFAULT_MONEY = 10.00;
};

//Test constructors
void test_Constructors();

//Test displayStats
void test_displayStats();

//Main, ONLY USED FOR TESTING
//COMMENT OUT OR DELETE BEFORE SUBMITTING
//int main() {
	//test_Constructors();
	//test_displayStats();
//}

//Constructor
//Initializes stats to default values
Character::Character() {
	name = "";
	time = DEFAULT_TIME;
	intelligence = DEFAULT_INTELLIGENCE;
	money = DEFAULT_MONEY;
	steps = 20;
}

//Constructor
//Name already known
Character::Character(string charName) {
	name = charName;
	time = DEFAULT_TIME;
	intelligence = DEFAULT_INTELLIGENCE;
	money = DEFAULT_MONEY;
}

//Constructor
//All player stats are given as arguments.
Character::Character(string charName, int timeIn, int intellIn, double moneyIn) {
	name = charName;
	time = timeIn;
	intelligence = intellIn;
	money = moneyIn;
}

//Display the stats of a character.
//COME BACK LATER TO FORMAT MONEY
void Character::displayStats() {
	cout << endl << name << "'s Stats:\n";
	cout << "intelligence: " << intelligence << endl;
	cout << "time: " << time << endl;
	cout << "money: " << fixed << setprecision(2) << money << "\n\n";
}

/*************************************************************************************/
/*************************************TESTING*****************************************/
/*************************************************************************************/
//Test constructors
void test_Constructors() {
	//Test variables
	int defTime = 25; //Default time is 25
	int defInt = 15; //Default intelligence is 15
	double defMon = 10.00; //Default money is 10.00
	//Test values entered by tester
	string testName;
	int testTime;
	int testInt;
	double testMon;
	//Test 1
	cout << "Constructor Tests\n";
	cout << "Test 1: Default constructor\n";
	Character character;
	//Check values
	assert("" == character.name);
	assert(defTime == character.time); 
	assert(defInt == character.intelligence); 
	assert(defMon == character.money); 
	cout << "\tTest 1 passed\n";
	//Test 2
	cout << "Test 2: Constructor with name\n";
	cout << "\tEnter your name: ";
	cin >> testName;
	character = Character(testName);
	//check values
	assert(testName == character.name);
	assert(defTime == character.time); 
	assert(defInt == character.intelligence); 
	assert(defMon == character.money); 
	cout << "\tTest 2 Passed\n";
	//Test 3
	cout << "Test 3: All stats used as arguments\n";
	cout << "\tEnter your name: ";
	cin >> testName;
	cout << "\tEnter the time: ";
	cin >> testTime;
	cout << "\tEnter the intelligence: ";
	cin >> testInt;
	cout << "\tEnter the money: ";
	cin >> testMon;
	character = Character(testName, testTime, testInt, testMon);
	//Check values
	assert(testName == character.name);
	assert(testTime == character.time); 
	assert(testInt == character.intelligence); 
	assert(testMon == character.money); 
	cout << "\tTest 3 passed\n";
}

//Test displayStats
//Already tested constructors, so know they set arguments correctly.
void test_displayStats() {
	//Variables
	string testName;
	int testTime;
	int testInt;
	double testMon;
	Character character;
	//Test 1
	cout << "displayStats test\n";
	cout << "Test 1: display default values\n";
	//Display default
	character.displayStats();
	cout << "\nTest 1 Passed\n";
	//Test 2
	cout << "Test 2: display custom name, other values default\n";
	cout << "\tEnter your name: ";
	cin >> testName;
	character = Character(testName);
	//Display name + default
	character.displayStats();
	cout << "\nTest 2 Passed\n";
	//Test 3
	cout << "Test 3: Input all stats and display them\n";
	cout << "\tEnter your name: ";
	cin >> testName;
	cout << "\tEnter the time: ";
	cin >> testTime;
	cout << "\tEnter the intelligence: ";
	cin >> testInt;
	cout << "\tEnter the money: ";
	cin >> testMon;
	character = Character(testName, testTime, testInt, testMon);
	//Display all entered input
	character.displayStats();
	cout << "\nTest 3 Passed\n";
	
}