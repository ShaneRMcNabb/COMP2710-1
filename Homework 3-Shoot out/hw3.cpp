/*
Sloan Kiechel
ssk0006
hw3.cpp
compile hw3.cpp then run it.
c/Users/sloan/Dropbox/Spring_2018/Software_Construction/Homeworks
*/
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iomanip>
using namespace std;
//Global variables: Track wins in simulations
int a_wins = 0;
int b_wins = 0;
int c_wins = 0;

//Prototypes
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
/* Input: A_alive indicates whether Aaron is alive. */
/*		  B_alive indicates whether Bob is alive. */
/* 		  C_alive indicates whether Charlie is alive. */
/* Return: true if at least two are alive */
/* 		   otherwise return false */

void Aaron_shoots1(bool& B_alive, bool& C_alive);
/* Strategy 1: Use call by reference
 * Input: B_alive indicates whether Bob alive or dead
 *  	  C_alive indicates whether Charlie is alive or dead.
 * Return: Change B_alive into false if Bob is killed.
 *		   Change C_alive into false if Charlie is killed. */

void Bob_shoots(bool& A_alive, bool& C_alive);
/* Call by reference
 * Input: A_alive indicates if Aaron is alive or dead
 *		   C_alive indicates whether Charlie is alive or dead
 * Return: Change A_alive into false if Aaron is killed.
 *			Change C_alive into false if Charlie is killed. */

void Charlie_shoots(bool& A_alive, bool& B_alive);
/* Call by reference
 * Input: A_alive indicates if Aaron is alive or dead
 * 		  B_alive indicates if Bob is alive or dead
 * Return: Change A_alive into false if Aaron is killed
 *		   Change B_alive into false if Bob is killed */
 
void Aaron_shoots2(bool& B_alive, bool& C_alive);
/* Strategy 2: Use call by reference
 * Input: B_alive indicates whether Bob is alive or dead
 *		  C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed
 *		   Change C_alive into false if Charlie is killed */
 
void duel_strat1(void);
/* No input.
 * Return: Change global variables a_wins, b_wins, and c_wins based on who wins.
 * Uses Strategy 1 */
 
 void duel_strat2(void);
/* No input.
 * Return: Change global variables a_wins, b_wins, and c_wins based on who wins.
 * Uses Strategy 2 */
 
/************************TESTING PROTOTYPES**************************************/
void test_atleast_two_alive(void);
/* This is a test driver for at_least_two_alive() */

void test_Aaron_shoots1(void);
/* This is a test driver for Aaron_shoots1 */

void test_Bob_shoots(void);
/* This is a test driver for Bob_shoots */

void test_Charlie_shoots(void);
/* This is a test driver for Charlie_shoots */

void test_Aaron_shoots2(void);
/* This is a test driver for Aaron_shoots */

/******************************************************************************/
/********************************MAIN******************************************/
/******************************************************************************/
int main() {
	cout.setf(ios::fixed | ios::showpoint);
	const int NUMBER_OF_DUELS = 10000;
	srand(time(0)); //Set random seed
	cout << "*** Welcome to Aubie's Duel Simulator ***\n";
	
	//Run tests
	test_atleast_two_alive();
	cout << "Press any key to continue...";
	cin.ignore().get(); //Pause command for Linux terminal
	test_Aaron_shoots1();
	cout << "Press any key to continue...";
	cin.ignore().get(); // Pause command for linux terminal
	test_Bob_shoots();
	cout << "Press any key to continue...";
	cin.ignore().get(); // Pause command for linux terminal
	test_Charlie_shoots();
	cout << "Press any key to continue...";
	cin.ignore().get(); // Pause command for linux terminal
	test_Aaron_shoots2();
	cout << "Press any key to continue...";
	cin.ignore().get(); // Pause command for linux terminal
	
	//Simulate 10000 duels Strat1
	cout << "Ready to test strategy 1 (run 10000 times):\n";
	cout << "Press any key to continue...";
	cin.ignore().get(); // Pause command for linux terminal
	cout << "...\n...\n...\n";
	int duelCount = 0;
	while (duelCount < NUMBER_OF_DUELS) {
		duel_strat1();
		duelCount++;
	}
	double a_percentage = (double) a_wins / (double) NUMBER_OF_DUELS;
	double b_percentage = (double) b_wins / (double) NUMBER_OF_DUELS;
	double c_percentage = (double) c_wins/ (double) NUMBER_OF_DUELS;
	int a_wins_Strat1 = a_wins; //Save a_wins to compare to strat 2
	cout << "Aaron won " << a_wins << "/" << NUMBER_OF_DUELS << " duels or " 
		 << setprecision(2) << a_percentage * 100 << "%\n";
	cout << "Bob won " << b_wins << "/" << NUMBER_OF_DUELS << " duels or "
		 << setprecision(2) << b_percentage * 100 << "%\n";
	cout << "Charlie won " << c_wins << "/" << NUMBER_OF_DUELS << " duels or "
		 << setprecision(2) << c_percentage * 100 << "%\n\n";	
	
	//Simulate 10000 duels Strat2
	cout << "Ready to test strategy 2 (run 10000 times):\n";
	cout << "Press any key to continue...";
	cin.ignore().get(); // Pause command for linux terminal
	cout << "...\n...\n...\n";
	//reset duel counts and wins
	duelCount = 0;
	a_wins = 0;
	b_wins = 0;
	c_wins = 0;
	while (duelCount < NUMBER_OF_DUELS) {
		duel_strat2();
		duelCount++;
	}
	a_percentage = (double) a_wins / (double) NUMBER_OF_DUELS;
	b_percentage = (double) b_wins / (double) NUMBER_OF_DUELS;
	c_percentage = (double) c_wins/ (double) NUMBER_OF_DUELS;
	cout << "Aaron won " << a_wins << "/" << NUMBER_OF_DUELS << " duels or " 
		 << setprecision(2) << a_percentage * 100 << "%\n";
	cout << "Bob won " << b_wins << "/" << NUMBER_OF_DUELS << " duels or "
		 << setprecision(2) << b_percentage * 100 << "%\n";
	cout << "Charlie won " << c_wins << "/" << NUMBER_OF_DUELS << " duels or "
		 << setprecision(2) << c_percentage * 100 << "%\n";	
		 
	//Compare strategies
	if (a_wins > a_wins_Strat1) {
		cout << "Strategy 2 is better than strategy 1\n";
	}
	else if (a_wins < a_wins_Strat1) {
		cout << "Strategy 1 is better than strategy 2\n";
	}
	else {
		cout << "The strategies have the same outcomes\n";
	}
}

/******************************************************************************/
/********************************Definitions***********************************/
/******************************************************************************/
/* Implementation of at_least_two_alive() */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
	//If Aaron is alive, check if Bob or Charlie is too
	if (A_alive) {
		if (B_alive || C_alive) {
				return true;
		}
	}
	//If Aaron is dead, check if Bob and Charlie are alive
	else if (B_alive) {
		if (C_alive) {
			return true;
		}
	}
	//If Bob and Aaron aren't alive, then there is no way two can be alive.
	else {
		return false;
	}
}

/* Implementation of Aaron_shoots1() */
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
	const int AARON_PROBABILITY = 33; // 1 out of 3 chance to hit
	int shoot_target_result;
	shoot_target_result = rand()%100;
	if (shoot_target_result <= 33) {
		//Aim at the most accurate shooter
		if (C_alive) {
			C_alive = false;
		}
		else {
			B_alive = false;
		}
	}
}

/* Implementation of Bob_shoots() */
void Bob_shoots(bool& A_alive, bool& C_alive) {
	const int BOB_PROBABILITY = 50; // 50% chance to hit
	int shoot_target_result;
	shoot_target_result = rand()%100;
	if (shoot_target_result <= 50) {
		//Aim at most accurate shooter
		if (C_alive) {
			C_alive = false;
		}
		else {
			A_alive = false;
		}
	}
	
}

/* Implementation of Charlie_shoots() */
void Charlie_shoots(bool& A_alive, bool& B_alive) {
	//Charlie always hits his target, so no random number needed.
	//Shoot at most accurate first (Bob)
	if (B_alive) {
		B_alive = false;
	}
	else {
		A_alive = false;
	}
}

/* Implementation of Aaron_shoots2() */
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
	//Aaron  misses his first shot. Aaron will not get a chance to shoot again
	//Until the other two have gone. Since Charlie never misses, either Bob or Charlie
	//Will be dead for the second shot. Thus, if both are alive, miss (first shot).
	const int AARON_PROBABILITY = 33; // 1 out of 3 chance to hit
	int shoot_target_result;
	if (!B_alive || !C_alive) {
		shoot_target_result = rand()%100;
		if (shoot_target_result <= 33) {
			//Aim at the most accurate shooter
			if (C_alive) {
				C_alive = false;
			}
			else {
				B_alive = false;
			}
		}	
	}
}

/* Implementation of duel_strat1() */
void duel_strat1(void) {
	//All start alive
	bool a_alive = true;
	bool b_alive = true;
	bool c_alive = true;
	while (at_least_two_alive(a_alive, b_alive, c_alive)) {
		if (a_alive) {
			Aaron_shoots1(b_alive, c_alive);
		}
		if (b_alive) {
			Bob_shoots(a_alive, c_alive);
		}
		if (c_alive) {
			Charlie_shoots(a_alive, b_alive);
		}
	}
	//Only one alive after loop, whoever alive is winner.
	if (a_alive) {
		a_wins++;
	}
	else if (b_alive) {
		b_wins++;
	}
	else {
		c_wins++;
	}
}

/* Implementation of duel_strat2() */
void duel_strat2(void) {
	//All start alive
	bool a_alive = true;
	bool b_alive = true;
	bool c_alive = true;
	while (at_least_two_alive(a_alive, b_alive, c_alive)) {
		if (a_alive) {
			Aaron_shoots2(b_alive, c_alive);
		}
		if (b_alive) {
			Bob_shoots(a_alive, c_alive);
		}
		if (c_alive) {
			Charlie_shoots(a_alive, b_alive);
		}
	}
	//Only one alive after loop, whoever alive is winner.
	if (a_alive) {
		a_wins++;
	}
	else if (b_alive) {
		b_wins++;
	}
	else {
		c_wins++;
	}
}

/*******************************************************************************/
/*****************************TESTING*******************************************/
/*******************************************************************************/
/* Implementation of test driver for at_least_two_alive() */
void test_atleast_two_alive(void) {
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";
	
	cout<< "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed...\n";
}

/* Implementation of test driver for Aaron_shoots1() */
void test_Aaron_shoots1(void) {
	cout << "Unit Test 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
	bool bob_alive;
	bool charlie_alive;
	
	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	bob_alive = true; 
	charlie_alive = true;
	Aaron_shoots1(bob_alive, charlie_alive);
	//Since aaron is shooting at charlie, Bob can't die
	assert(true == bob_alive);
	if (charlie_alive) {
		cout << "\t\tAaron misses.\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}
	
	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	bob_alive = false; 
	charlie_alive = true;
	Aaron_shoots1(bob_alive, charlie_alive);
	//Aaron is shooting at charlie and bob is already dead
	assert(false == bob_alive);
	if (charlie_alive) {
		cout << "\t\tAaron misses.\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}
	
	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	bob_alive = true; 
	charlie_alive = false;
	Aaron_shoots1(bob_alive, charlie_alive);
	//Aaron is shooting at bob and charlie is already dead
	assert(false == charlie_alive);
	if (bob_alive) {
		cout << "\t\tAaron misses.\n";
	}
	else {
		cout << "\t\tBob is dead.\n";
	}
	
}

/* Implementation of test driver for Bob_shoots() */
void test_Bob_shoots(void) {
	cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
	bool a_alive;
	bool c_alive;
	
	cout << "\tCase 1: Aaron alive, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a_alive = true;
	c_alive - true;
	Bob_shoots(a_alive, c_alive);
	//Bob is shooting at charlie, so Aaron has to stay alive
	assert(true == a_alive);
	if (c_alive) {
		cout << "\t\tBob missed\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}
	
	cout << "\tCase 2: Aaron dead, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a_alive = false;
	c_alive - true;
	Bob_shoots(a_alive, c_alive);
	//Bob is shooting at charlie, and aaron is already dead
	assert(false == a_alive);
	if (c_alive) {
		cout << "\t\tBob missed\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}
	
	cout << "\tCase 3: Aaron alive, Charlie dead\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a_alive = true;
	c_alive = false;
	Bob_shoots(a_alive, c_alive);
	//Bob is shooting at Aaron, charlie is already dead
	assert(false == c_alive);
	if (a_alive) {
		cout << "\t\tBob missed\n";
	}
	else {
		cout << "\t\tAaron is dead.\n";
	}
}

/* Implementation of test driver for Charlie_shoots() */
void test_Charlie_shoots(void) {
	cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
	bool a_alive;
	bool b_alive;
	
	cout << "\tCase 1: Aaron alive, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	a_alive = true;
	b_alive = true;
	Charlie_shoots(a_alive, b_alive);
	//Charlie is shooting at Bob, so Aaron can't die.
	assert(true == a_alive);
	//Since charlie doesn't miss, bob must die.
	assert(false == b_alive);
	cout << "\t\tBob is dead.\n";
	
	cout << "\tCase 2: Aaron dead, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	a_alive = false;
	b_alive = true;
	Charlie_shoots(a_alive, b_alive);
	//Charlie is shooting at Bob, aaron already dead
	assert(false == a_alive);
	//Since charlie doesn't miss, bob must die.
	assert(false == b_alive);
	cout << "\t\tBob is dead.\n";
	
	cout << "\tCase 3: Aaron alive, Bob dead\n";
	cout << "\t\tCharlie is shooting at Aaron\n";
	a_alive = true;
	b_alive = false;
	Charlie_shoots(a_alive, b_alive);
	//Charlie is shooting at Aaron, bob is already dead.
	assert(false == b_alive);
	//Since charlie doesn't miss, Aaron must die.
	assert(false == a_alive);
	cout << "\t\tAaron is dead.\n";
}

/* Implementation of test driver for Aaron_shoots2() */
void test_Aaron_shoots2(void) {
	cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
	bool b_alive;
	bool c_alive;
	
	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron intentionally misses his first shot\n";
	b_alive = true;
	c_alive = true;
	Aaron_shoots2(b_alive, c_alive);
	assert(true == b_alive);
	assert(true == c_alive);
	cout << "\t\tBoth Bob and Charlie are alive\n";
	
	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	b_alive = false;
	c_alive = true;
	Aaron_shoots2(b_alive, c_alive);
	//Aaron is shooting at charlie and bob is already dead
	assert(false == b_alive);
	if (c_alive) {
		cout << "\t\tAaron misses\n";
	}
	else {
		cout << "\t\tCharlie is dead\n";
	}
	
	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	b_alive = true;
	c_alive = false;
	Aaron_shoots2(b_alive, c_alive);
	//Aaron is shooting at bob and charlie is already dead
	assert(false == c_alive);
	if (b_alive) {
		cout << "\t\tAaron misses\n";
	}
	else {
		cout << "\t\tBob is dead\n";
	}
}
