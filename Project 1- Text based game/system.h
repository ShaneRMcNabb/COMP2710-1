/*
* Sloan Kiechel
* ssk0006
* system.h
* system header to link system.cpp
* Resource that taught how to use header: 
* http://www.learncpp.com/cpp-tutorial/19-header-files/
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <iomanip> 

using namespace std;


#ifndef SYSTEM_H
#define SYSTEM_H
#include "menu.h" //Menu class
#include "character.h" //Character class
#include "encounter.h" //Encounter class
#include "puzzle.h" //Puzzle class

//High score struct 
struct Highscore {
	string name;
	int score;
};

class System {
	public:
		System(); //Constructor
		void startMenu(); //Calls the start menu, waits for choices.
		void gameStep(); //Steps to next move in game
		void displayHighScore(); //Display high scores
		void addHighScore(string name, int score); //Adds high score
		Character getCharacter(); //Returns the character so other classes can use it.
		void setScoreFile(string filename); //Changes highscore file, refills array (USED FOR TESTING)
		bool replay(); //Sees if player wants to play again
		void readPapers(); //Lose time, gain intel
		void changeSearch(); //Lose time, gain money
		void endGame(bool win); //End game
	private:
		void fillScoreArray(); //Create score array for high scores
		void emptyScoreArray(); //Clears score array
		double fRand(double fMin, double fMax); //Rand function for double
		void writeHighScore(); // Writes highscore to file
		static const int MAX_SCORES = 10; //Max number of high scores to show
		static const int FIXED_TIME_LOSS = 1; //Time loss for collecting change or reading papers
		Character player;
		Menu menu;
		EncounterControl encounter;
		PuzzleControl puzzle;
		int numOfScores; //Number of high scores in file
		string highScoreFile; //File name for highscore
		Highscore highscore_array[MAX_SCORES]; //highscore array
		bool start;
		bool name;
		int fixedTimeLoss; //Time loss for collecting change or reading papers
};
#endif
