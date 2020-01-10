#include "display.h"
#include "GL/glew.h"
#include <iostream>
#include "Game.h"
#include "Transform.h"
#include <cstdlib>

display::display() //definition of display function
{
}

bool display::isClosed() //definition of isClosed function
{
	return _isClosed; //returns the value of the _isClosed bool
}

void display::clear(float r, float g, float b, float a) //definition of clear function taking in 4 floats as arguments 
{
	//glClearDepth(1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears colour buffer and fills it with selected colour
}

void display::returnError(std::string errorString) //definition of returnError function that takes in a string as an argument
{
	std::cout << errorString << std::endl; //displays error message
	std::cout << "press any  key to quit..."; //prompts user to enter key to exit 
	int in;
	std::cin >> in; //takes in input from the user
	SDL_Quit(); //shuts down all SDL subsystems
}

display::~display() //definition for ~display destructor 
{
	SDL_GL_DeleteContext(gameContext); //deletes context
	SDL_DestroyWindow(displayWindow); //deletes window
	SDL_Quit(); //shuts down all SDL subsystems
}

void display::update() //definition for Update function 
{
	
	SDL_GL_SwapWindow(displayWindow); //swaps buffers (What openGL has drawn is swapped onto the display window)
	SDL_Event e;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	while (SDL_PollEvent(&e))
	{
		
		if (e.type == SDL_QUIT)
			_isClosed = true;
	}
}

void display::initDisplay(int width, int height, const std::string& windowName) //definition for initDisplay functiom that takes in 2 ints and a const string
{
	SDL_Init(SDL_INIT_EVERYTHING); //initialises SDL
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //minimum number of bits used to disply red colours on screen
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); //minimum number of bits used to disply green colours on screen
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); //minimum number of bits used to disply blue colours on screen
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //minimum number of bits used to disply alpha colours on screen
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //minimum number of bits allocated to display colours 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //minimum number of bits allocated to display depth
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //allocates space for a second window for things to be drawn in before they are sent to the screen

	displayWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); //creates window
	gameContext = SDL_GL_CreateContext(displayWindow); //creates context

	GLenum currentStatus = glewInit();

	if (currentStatus != GLEW_OK)
	{
		std::cerr << "Glew failed" << std::endl; //error message if glew does not intialise 

	}
	_isClosed = false; //sets _isClosed to false

	
	

	if (displayWindow == nullptr)
	{
		returnError("window failed to create"); //error message if window fails to create
	}

	//gameContext = SDL_GL_CreateContext(displayWindow);

	if (gameContext == nullptr)
	{
		returnError("SDL_GL context failed to create"); //error message if context fails to create
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise"); //error message if GLEW does not initialise
	}
	float a = 1.0f;
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //creates random float value that will be used for the red value in glclearcolour 
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //creates random float value that will be used for the green value in glclearcolour 
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //creates random float value that will be used for the blue value in glclearcolour 
	
	glClearColor(r, g, b, a); //uses random red, green and blue values along with the 1.0 alpha value to colour the display (previously mentioned selected colour from clear function)
}