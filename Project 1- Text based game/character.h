/*
* Sloan Kiechel
* ssk0006
* menu.h
* character header to link character.cpp
* Resource that taught how to use header: 
* http://www.learncpp.com/cpp-tutorial/19-header-files/
*/

#include <string>
using namespace std;

#ifndef CHARACTER_H
#define CHARACTER_H

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
		int steps;
		void displayStats(); //Displays character stats
	private:
		//Default values
		static const int DEFAULT_TIME = 25;
		static const int DEFAULT_INTELLIGENCE = 15;
		static const double DEFAULT_MONEY = 10.00;
};

#endif