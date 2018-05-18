/*
* Sloan Kiechel
* ssk0006
* puzzle.h
* puzzle header to link puzzle.cpp
* Resource that taught how to use header: 
* http://www.learncpp.com/cpp-tutorial/19-header-files/
*/


#ifndef PUZZLE_H
#define PUZZLE_H
#include "character.h" //Character class

//puzzle class
//Controls the puzzles
class PuzzleControl {
	public:
		PuzzleControl(Character playerIn); //Constructor
		PuzzleControl(); //Default Constructor
		void setCharacter(Character playerIn); //Set player
		Character randomPuzzle();
	private:
		static const int NUMBER_OF_PUZZLES = 6; //Number of different encounters
		Character player;
		void shelbyOpen(); //when did shelby open
		void bigger(); //bigger family question
		void farmer(); //how many sheep
		void months(); //how many months with 28 days
		void pattern(); //letter pattern
		void jimmy(); //jimmys family
		double fRand(double fMin, double fMax); //Rand function for double
		void verifyInput(); //makes sure input is good.
		int playerAnswer; // player answer
};

#endif