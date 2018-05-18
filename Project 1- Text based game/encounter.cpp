/*
* Sloan Kiechel
* ssk0006
* encounter.cpp
*
* To compile System enter the following:
* g++ menu.cpp character.cpp system.cpp encounter.cpp puzzle.cpp -o encounter

* Note: This is only for encounter.cpp, The file "game.cpp" instructs how to compile and run the entire game.
* Also Note: If trying to commpile this seperately with the above, you have to uncomment main().
*
* Additional resource: Double rand on stack overflow: 
* https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip> 
#include "character.h" //Character class
using namespace std;

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

//Used for testing. Comment out before submitting.
//int main() {
	
//}

//default constructor
EncounterControl::EncounterControl() {
	srand(time(0)); //Sets random seed
}

//Constructor
//Takes in a character and sets it to player
EncounterControl::EncounterControl(Character playerIn) {
	srand(time(0)); //Sets random seed
	player = playerIn;
}

//Sets player to playerIn
void EncounterControl::setCharacter(Character playerIn) {
	player = playerIn;
}

//Sets a random encounter
Character EncounterControl::randomEncounter() {
	cout << endl; //Formatting
	int randNum = rand() % NUMBER_OF_ENCOUNTERS; //Randomly choose from encounters
	switch (randNum) {
		case 0:
			professor();
			break;
		case 1: 
			gradStudent();
			break;
		case 2: 
			papersToGrade();
			break;
		case 3: 
			banana();
			break;
		case 4:
			ex();
			break;
		case 5: 
			watch();
			break;
		default: 
			cout << "The programmer screwed up\n";
			break;
	}
	cout << endl; //Formatting
	return player;
}

//Encounter a professor
//Lose time. Chance to gain intelligence.
void EncounterControl::professor() {
	cout << "You have encountered a professor!\n";
	//80% chance to lose 1 time and gain 1-3 intelligence
	//20% chance to lose 3 time and gain 5-8 intelligence
	int randNum = rand() % 100;
	int intelChange;
	int timeChange;
	if (randNum < 80) {
		cout << "You have a quick, but educational conversation\n";
		intelChange = rand() % 3 + 1;
		cout << "You gain " << intelChange << " intelligence and lose 1 time\n";
		timeChange = 1;
	}
	else {
		cout << "Your professor gives you a personal lecture. It was very informative, but took a long time.\n";
		intelChange = rand() % 3 + 5;
		cout << "You gain " << intelChange << " intelligence and lose 3 time\n";
		timeChange = 3;
	}
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - timeChange;
	player.steps = player.steps -1; //1 step closer to end
}

//Encounter a gradStudent
//Lose time, chance to gain or lose intelligence. Lose 1 time
void EncounterControl::gradStudent() {
	cout << "You have encountered a graduate student!\n";
	//60% chance to gain 1-3 intelligence
	//30% chance to gain no intelligence
	//10% chance to lose 1-3 intelligence
	int randNum = rand() % 100;
	int intelChange;
	int timeChange = 1;
	if (randNum < 60) {
		cout << "The graduate student explains a hard concept to you\n";
		intelChange = rand() % 3 + 1;
		cout << "You gain " << intelChange << " intelligence and lose 1 time\n";
	}
	else if (randNum >= 60 && randNum < 90) {
		cout << "The graduate student is swamped with work and runs past without having any sort of conversation with you\n";
		intelChange = 0;
		cout << "You lose 1 time\n";
	}
	else {
		cout << "The graduate student poorly explains a concept\n";
		intelChange = rand() % 3 + 1;
		cout << "You lose " << intelChange << " intelligence and lose 1 time\n";
		intelChange = 0 - intelChange;
	}
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - timeChange;
	player.steps = player.steps -1; //1 step closer to end
}

double EncounterControl::fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

//Encounter papers to grade
//Lose time, chance to lose/gain money
void EncounterControl::papersToGrade() {
	cout << "You encounter papers you need to grade!\n";
	//75% chance to gain $1.00-$5.00, lose 1 time
	//20% chance to gain $3.00 -$8.00, lose 3 time
	//5% chance to lose $1.00-$5.00, lose 3 time
	int randNum = rand() % 100;
	double moneyChange;
	int timeChange;
	if (randNum < 75) {
		cout << "You quickly grade the papers\n";
		moneyChange = fRand(1.0, 5.0);
		cout << "You gain $" << fixed << setprecision(2) << moneyChange << " and lose 1 time\n";
		timeChange = 1;
	}
	else if (randNum >= 75 && randNum < 95) {
		cout << "You expertly grade the papers. It takes a long time, but you are rewarded with a bonus\n";
		moneyChange = fRand(3.0, 8.0);
		cout << "You gain $" << fixed << setprecision(2) << moneyChange << " and lose 3 time\n";
		timeChange = 3;
	}
	else {
		cout << "You attempted to grade the papers but made several errors. The professor chews you out and requires "
			<< "you pay for another student to regrade the papers\n";
		moneyChange = fRand(1.0, 5.0);
		cout << "You lose $" << fixed << setprecision(2) << moneyChange << " and lose 3 time\n";
		moneyChange = 0 - moneyChange;
		timeChange = 3;
	}
	player.money = player.money + moneyChange;
	player.time = player.time - timeChange;
	player.steps = player.steps -1; //1 step closer to end
}

//Slip on a banana
//Chance to gain/lose steps and intelligence
void EncounterControl::banana() {
	cout << "You encounter a banana peel!\n";
	//33% chance to slip and slide back lose 1-5 intelligence, 2-3 steps back
	//33% chance to slip forward, gain 1-3 intelligence, move 2-3 steps forward
	//34% chance to step over the peel. -1 time, move forward 1 step.
	int randNum = rand() % 100;
	int stepChange;
	int timeChange = 1;
	int intelChange;
	if (randNum < 33) {
		cout << "You slip on the peel, sliding back several steps\n";
		intelChange = rand() % 3 + 1;
		stepChange = rand() % 2 + 1;
		cout << "You lose " << intelChange << " intelligence and move back " << stepChange << " steps\n";
		intelChange = 0 - intelChange;
		stepChange = 0 - stepChange;
	}
	else if (randNum >= 33 && randNum < 66) {
		cout << "You decide to run and jump on the peel, sliding forward several spaces\n";
		intelChange = rand() % 3 + 1;
		stepChange = rand() % 2 + 1;
		cout << "You gain " << intelChange << " intelligence and move forward " << stepChange << " steps\n";
	}
	else {
		cout << "You step over the banana peel like any normal person would\n";
		intelChange = 0;
		stepChange = 1;
		cout << "You move forward one step and lose 1 time\n";
	}
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - timeChange;
	player.steps = player.steps - stepChange;
}

//Encounter ex-lover
//Lose 1-3 steps, 1-3 time
void EncounterControl::ex() {
	cout << "You encounter your ex-lover\n";
	int stepChange = rand() % 3 + 1;
	int timeChange = rand() % 3 + 1;
	cout << "You turn around and run away\n";
	cout << "You move back " << stepChange << " steps and lose " << timeChange << " time\n";
	player.steps = player.steps + stepChange;
	player.time = player.time - timeChange;
}

//Encounter a watch
//Gain 1-5 time
void EncounterControl::watch() {
	cout << "You find a watch!\n";
	int timeChange = rand() % 5 + 1;
	cout << "You realize you have more time to get out!\n";
	cout << "You gain " << timeChange << " time\n";
	player.time = player.time + timeChange;
	player.steps = player.steps - 1;
}