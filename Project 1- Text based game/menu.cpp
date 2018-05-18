/*
* Sloan Kiechel
* ssk0006
* menu.cpp

* to compile:
* g++ -o menu menu.cpp
* 
* Note: That only compiles menu.cpp. For the entire game, see "game.cpp"
* Also Note: If trying to commpile this seperately with the above, you have to uncomment main().
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <iomanip> 
using namespace std;

//Menu class.
//Creates game and main menus and handles input errors.
class Menu {
	public:
		Menu(); //Constructor
		int gameMenu(); //Display game menu and get input
		int mainMenu(); //Display main menu and get input
	private:
		int playerChoice; //Player input
		void verifyGameMenuInput(); //Ensure game menu input is valid
		void verifyMainMenuInput(); //Ensure main menu input is valid
};

//Test main menu
void test_mainMenu();

//Test game menu
void test_gameMenu();

//Main, ONLY USED FOR TESTING
//COMMENT OUT OR DELETE BEFORE SUBMITTING
//int main() {
	//test_gameMenu();
	//test_mainMenu();
//}

//Constructor. Sets playerChoice to 0.
Menu::Menu() {
	playerChoice = 0;
}

//Displays the main menu,returns player input
int Menu::mainMenu() {
	//Main menu
	cout << "\n\t1) Start a new game of Escape Shelby!\n";
	cout << "\t2) View top 10 High Scores\n";
	cout << "\t3) Quit game\n\n";
	cout << "Please choose an option: ";
	//Get input
	cin >> playerChoice;
	//Validate input
	verifyMainMenuInput();
	return playerChoice;
	
}

//Verify the input is valid
//If input is not valid, prompt for proper input.
void Menu::verifyMainMenuInput() {
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail() || playerChoice < 1 || playerChoice > 3) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please input a menu number, or enter -1 to exit the game.\n";
		cout << "\nPlease choose an action: ";
		cin >> playerChoice;
		//If player chooses quit
		if (playerChoice == -1) {
			exit(1);
		}
	}
}

//Displays the menu, then gets the player's input.
//Returns the player's menu choice.
int Menu::gameMenu() {
	//Display the menu
	cout << "\t1) Move forward (takes time, could be risky...)\n";
	cout << "\t2) Read technical papers (boost intelligence, takes time)\n";
	cout << "\t3) Search for loose change (boost money, takes time)\n";
	cout << "\t4) View character\n";
	cout << "\t5) Quit the game\n\n";
	cout << "Please choose an action: ";
	//Get input
	cin >> playerChoice;
	//Validate input
	verifyGameMenuInput();
	return playerChoice;
}

//Verify the input is valid
//If input is not valid, prompt for proper input.
void Menu::verifyGameMenuInput() {
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail() || playerChoice < 1 || playerChoice > 5) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please input a menu number, or enter -1 to exit the game.\n";
		cout << "\nPlease choose an action: ";
		cin >> playerChoice;
		//If player chooses quit
		if (playerChoice == -1) {
			exit(1);
		}
	}
}

/*************************************************************************************/
/*************************************TESTING*****************************************/
/*************************************************************************************/
//Test main menu
void test_mainMenu() {
	cout << "mainMenu Test\n";
	cout << "Test 1: good input\n";
	cout << "Enter a name, then Enter 1 as input\n\n";
	Menu menu;
	int choice;
	choice = menu.mainMenu();
	assert(1 == choice);
	cout << "Test 2: bad input first, then valid\n";
	cout << "Enter your name, then Enter bad input, then enter 2\n\n";
	choice = menu.mainMenu();
	assert(2 == choice);
	cout << "Test 3: Bad input then quit\n";
	cout << "Enter your name, then Enter bad input, then -1 to quit\n\n";
	choice = menu.mainMenu();
}
//Test game menu
void test_gameMenu() {
	cout << "gameMenu Test\n";
	cout << "Test 1: good input\n";
	cout << "Enter 1 as input\n\n";
	Menu menu;
	int choice;
	choice = menu.gameMenu();
	assert(1 == choice);
	cout << "Test 2: bad input first, then valid\n";
	cout << "Enter bad input, then enter 2\n\n";
	choice = menu.gameMenu();
	assert(2 == choice);
	cout << "Test 3: Bad input then quit\n";
	cout << "Enter bad input, then -1 to quit\n\n";
	choice = menu.gameMenu();
}
