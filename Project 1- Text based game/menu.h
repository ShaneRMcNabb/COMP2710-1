/*
* Sloan Kiechel
* ssk0006
* menu.h
* menu header to link menu.cpp
* Resource that taught how to use header: 
* http://www.learncpp.com/cpp-tutorial/19-header-files/
*/

#ifndef MENU_H
#define MENU_H

//Menu class
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

#endif