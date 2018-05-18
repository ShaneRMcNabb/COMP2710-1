/*
* Sloan Kiechel
* ssk0006
* game.cpp
* The file that pulls it all together.
*
* To compile: 
* g++ menu.cpp character.cpp system.cpp encounter.cpp puzzle.cpp game.cpp -o game
c/Users/sloan/Dropbox/Spring_2018/Software_Construction/Project1
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip> 
#include "system.h" //System class
#include "menu.h" //Menu class
#include "character.h" //Character class
#include "encounter.h" //Encounter class
#include "puzzle.h" //Puzzle class
using namespace std;

//Starts/runs the game
int main() {
	System system;
	system.startMenu();
}