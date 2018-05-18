/*
* Sloan Kiechel
* ssk0006
* puzzle.cpp
*
* To compile System enter the following:
* g++ menu.cpp character.cpp system.cpp encounter.cpp puzzle.cpp -o puzzle

* Note: This is only for puzzle.cpp, The file "game.cpp" instructs how to compile and run the entire game.
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

//Used for testing. Comment out when submitting.
//int main() {
	
//}

//default constructor
PuzzleControl::PuzzleControl() {
	srand(time(0)); //Sets random seed
}

//Constructor
//Takes in a character and sets it to player
PuzzleControl::PuzzleControl(Character playerIn) {
	srand(time(0)); //Sets random seed
	player = playerIn;
}

//Sets player to playerIn
void PuzzleControl::setCharacter(Character playerIn) {
	player = playerIn;
}


//Sets a random puzzle
Character PuzzleControl::randomPuzzle() {
	cout << endl;
	int randNum = rand() % NUMBER_OF_PUZZLES; //Randomly choose from encounters
	switch (randNum) {
		case 0:
			shelbyOpen();
			break;
		case 1: 
			bigger();
			break;
		case 2: 
			farmer();
			break;
		case 3: 
			months();
			break;
		case 4:
			pattern();
			break;
		case 5: 
			jimmy();
			break;
		default: 
			cout << "The programmer screwed up\n";
			break;
	}
	return player;
}

//random with double
double PuzzleControl::fRand(double fMin, double fMax) {
	
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

//What year was shelby opened?
//Chance to win/lose money.
void PuzzleControl::shelbyOpen() {
	cout << "A tour group passes by and one of the parents  wants to know when the shelby center first opened\n";
	cout << "Your choices are:\n1) 1997\n2) 2003\n3) 2007\n4) 1990\n";
	cout << "What is your answer? (Enter a number 1-4): ";
	cin >> playerAnswer;
	verifyInput();
	cout << endl; //Formatting
	int timeChange;
	double moneyChange;
	//Correct answer
	if (playerAnswer == 3) {
		moneyChange = fRand(.50, 5.75);
		cout << "You answered correctly. The parent tips you $" << fixed << setprecision(2) << moneyChange << endl;
		timeChange = 1;
	}
	else { //Wrong answer
		timeChange = rand() % 5 + 1;
		moneyChange = 0;
		cout << "You answered incorrectly. The tour guide corrects you and lectures you about the history of the Shelby center\n";
		cout << "You lose " << timeChange << " time\n";
	}
	player.time = player.time - timeChange;
	player.money = player.money + moneyChange;
	player.steps = player.steps - 1; //Move 1 step closer.
	cout << endl; //Formatting
}

//Puzzle about bigger family
//Chance to gain/lose intelligence.
void PuzzleControl::bigger() {
	cout << "Your english Teacher stops you in the hallway. She tells you if you can answer a riddle correctly, she will "
		<< " give you an A in her class.\n";
	cout << "The riddle is: \n";
	cout << "Who is bigger: Mr.Bigger, Mrs.Bigger, or their Baby?\n";
	cout << "1) Mr.Bigger\n2) Mrs.Bigger\n3) the baby\n4) Try to run away\n";
	cout << "What is your answer? (Enter a number 1-4): ";
	cin >> playerAnswer;
	verifyInput();
	cout << endl; //Formatting
	int intelChange;
	int timeChange = 1;
	int stepChange = 1;
	//Try to run away: 20% chance successful, 80% chance unsuccessful
	if (playerAnswer == 4) {
		int randNum = rand() % 100;
		if (randNum < 80) {
			cout << "Your teacher grabs your arm, gives you a long lecture, and gives you an F in her class\n";
			cout << "You lose 5 intelligence and 3 time\n";
			timeChange = 3;
			intelChange = -5;
		}
		else {
			cout << "You somehow manage to sprint past your teacher. She is angry and fails you.\n";
			cout << "You lose 5 intelligence but move 5 steps forward\n";
			intelChange = -5;
			stepChange = 5;
		}
	}
	else if (playerAnswer == 3) {
		cout << "You answer: \"The baby because he is a little Bigger\" and your teacher is amazed!\n";
		cout << "You gain 5 intelligence\n";
		intelChange = 5;
	}
	else {
		cout << "You answer incorrectly. The teacher shakes her head dissapointedly.\n";
		cout << "You lose 3 intelligence\n";
		intelChange = -3;
	}
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - timeChange;
	player.steps = player.steps - stepChange;
	cout << endl; //Formatting
}

//Puzzle about farmer's sheep
//gain/lose intelligence
void PuzzleControl::farmer() {
	cout << "A farmer approaches you. He asks \"If I have seventeen sheep all but nine die, how many do I have left?\"\n";
	cout << "1) 17\n2) 9\n3) 8\n4) 26\n";
	cout << "What is your answer? (enter a number 1-4): ";
	cin >> playerAnswer;
	verifyInput();
	cout << endl; //Formatting
	int intelChange;
	if (playerAnswer == 2) {
		cout << "\"That is how many sheep I have left!\" The farmer exclaims\n";
		cout << "You gain 2 intelligence\n";
		intelChange = 2;
	}
	else {
		cout << "The farmer looks at you confused, trying to count on his fingers. Your answer is clearly wrong\n";
		cout << "You lose 2 intelligence\n";
		intelChange = -2;
	}
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - 1;
	player.steps = player.steps - 1;
	cout << endl; //Formatting
}

//How many months have 28 days?
//Win money
void PuzzleControl::months() {
	cout << "Jeff Foxworthy pulls you into a room. The room has a full audience and camera crew and Jeff "
		<< "exclaims \"It is time to see if you are smarter than a 5th grader!\"\n";
	cout << "Your question is: how many months have 28 days?\n";
	cout << "What is your answer? (enter a number): ";
	cin >> playerAnswer;
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please enter a valid answer : ";
		cin >> playerAnswer;
	}
	cout << endl; //Formatting
	if (playerAnswer == 12) {
		cout << "Jeff looks very impressed as he announces you got the answer correctly. The audience cheers.\n";
		cout << "You win $20.00!";
		player.money = player.money + 20.0;
	}
	else {
		cout << "Jeff looks dissapointed. \"It turns out that " << player.name << " is not smarter than a 5th grader\"\n";
		cout << "You lose 5 intelligence\n";
		player.intelligence = player.intelligence - 5;
	}
	player.steps = player.steps - 1;
	cout << endl; //formatting
}

//Letter pattern that corresponds to months
//Gain intelligence or lose time.
void PuzzleControl::pattern() {
	cout << "A troll appears! He says you can only pass if you can finish the last 3 letters in the following pattern:\n";
	cout << "J, F, M, A, M, J, J, A, ...\n";
	cout << "1) S, O, N\n2) J, F, M\n3) A, S, S\n4) O, S, N\n";
	cout << "What is your answer? (enter a number 1-4): ";
	cin >> playerAnswer;
	verifyInput();
	cout << endl; //formatting
	int intelChange = 0;
	int timeChange = 1;
	if (playerAnswer == 1) {
		cout << "The troll is very impressed that you figured out each letter was the beginning of a month. He lets you pass.\n";
		cout << "You gain 3 intelligence\n";
		intelChange = 3;
	}
	else if (playerAnswer == 3) {
		cout << "The troll rolls his eyes. He is not impressed by your childish answer. He makes you stay until you "
			<< "eventually solve the problem.\n";
		cout << "You lose 3 time\n";
		timeChange = 3;
	}
	else {
		cout << "Your answer is incorrect. You lose one intelligence and spend 3 time trying to pass the troll\n";
		timeChange - 3;
		intelChange = -1;
	}
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - timeChange;
	player.steps = player.steps - 1;
	cout << endl; //Formatting
}

//Jimmy's family puzzle
//Gain nothing, lose time.
void PuzzleControl::jimmy() {
	cout << "A kid runs up and gets in your way. He says \"My name is Jimmy. You can't pass until you answer my riddle. \n"
		<< "The riddle is: if my Mom had 4 kids and she named the first Monday, the second Tuesday, and the third " 
		<< "Wednesday, what is the name of the 4th child\"\n";
	cout << "1) Bob\n2) Thursday\n3) Jimmy \n4) Friday\n";
	cout << "What is your answer? (enter a number 1-4): ";
	cin >> playerAnswer;
	verifyInput();
	cout << endl; //Formatting
	if (playerAnswer == 3) {
		cout << "Jimmy jumps up and down excitedly. Your answer was correct\n";
		cout << "The answer was so simple however, that you gain nothing\n";
		player.time = player.time - 1;
	}
	else {
		cout << "Jimmy starts crying because you got the answer wrong. You spend time consoling him\n";
		cout << "You lose 3 time\n";
		player.time = player.time - 3;
	}
	player.steps = player.steps - 1;
	cout << endl; //Formatting
}

void PuzzleControl::verifyInput() {
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail() || playerAnswer < 1 || playerAnswer > 4) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please enter a valid answer : ";
		cin >> playerAnswer;
	}
}