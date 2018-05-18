/*
* Sloan Kiechel
* ssk0006
* encounter.h
* encounter header to link encounter.cpp
* Resource that taught how to use header: 
* http://www.learncpp.com/cpp-tutorial/19-header-files/
*/

#ifndef ENCOUNTER_H
#define ENCOUNTER_H
#include "character.h" //Character class

//encounter class
//Controls the encounters 
class EncounterControl {
	public:
		EncounterControl(Character playerIn); //Constructor
		EncounterControl(); //Default Constructor
		void setCharacter(Character playerIn); //Set player
		Character randomEncounter();
	private:
		static const int NUMBER_OF_ENCOUNTERS = 6; //Number of different encounters
		Character player;
		void professor(); //encounter professor
		void gradStudent(); //encounter grad student
		void papersToGrade(); //encounter papers to grade
		void banana(); //encounter/slip on banana
		void ex(); //encounter ex
		void watch(); //find watch
		double fRand(double fMin, double fMax); //Rand function for double
};

#endif