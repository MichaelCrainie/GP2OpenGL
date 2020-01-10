#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <cstdlib>
class display
{
public:
	display(); //declaration for display function (constructor) 
	void update(); //declaration for Update function (buffer swap method)
	bool isClosed(); //declaration for isClosed function 
	void clear(float r, float g, float b, float a); //declaration for Clear function that takes in 4 floats as arguments
	void initDisplay(int width, int height, const std::string& windowName); //declaration for initDisplay that takes in 2 ints and a const string as arguments 
	virtual ~display(); //declaration for ~display function (deconstructor)
    //float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
	//float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
	//float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
	
protected:
private:
	
	
	void returnError(std::string errorString); //declaration for returnError that takes in a string as an argument

	SDL_Window* displayWindow; //creates variable named displayWindow of type SDL_Window
	SDL_GLContext gameContext; //creates variable named gameContext that is of type SDL_GLCONTEXT
	bool _isClosed; //creates a bool variable named _isClosed
};

