// MichaelCrainieOPENGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include <ctime>



int main(int argc, char** argv)
{
	srand(static_cast <unsigned> (time(0))); //used to enable generation of randoms
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
	//float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
	//float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
	Game game; //creates a Game class named game
	game.run(); //calls the run function from game
	return 0;
}

