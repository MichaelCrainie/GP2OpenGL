#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Audio.h"



enum class GameState { PLAY, EXIT }; //possible game states

class Game
{
public:
	Game(); //declaration for Game function (Constructor)
	~Game(); //declaration for ~Game function (Deconstructor)

	void run(); //declaration for Run function

private:

	void initSystems(); //initSystems function 
	void processInput(); //processInput function 
	void gameLoop(); //gameLoop function
	void drawGame(); //drawGame function 
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad); //collision function that takes in 2 glm:vec3s and 2 floats as arguments
	void playAudio(unsigned int Source, glm::vec3 pos); //playAudio function that takes in an unsigned int and glm::vec3 as arguments

	display mainDisplay;
	GameState _gameState;
	glm::vec3 vec3example;
	float counter;
	Audio audioDevice;

	unsigned int backGroundMusic; //creates unsigned int named backGroundMusic 
	unsigned int collisionSound; //creates unsigned int named collisionSound
	unsigned int fireSound; //creates unsigned int named fireSound
	float playerXValue = 0.0f; //creates float named playerXValue and sets it to 0.0f
	float playerYvalue = -3.75f; //creates float named playerYValue and sets it to -3,75f
	float playerZValue = 0.0f; //creates float named playerZValue and sets it to 0.0f;
	float monkeyHeadXValue = 4.0f; //creates float named monkeyHeadXValue and sets it to 4.0f;
	float monkeyHeadYValue = 3.5f; //creates float named monkeyHeadYValue and sets it to 3.5f;
	float missileYValue = -3.55f; //creates a float named missileYValue and sets it to -3.55f;
	int timer = 10; //creates an int named timer and sets it to 10
	int health = 10; //creates an int named health and sets it to 10
	bool moveRight = true; //creates a bool named moveRight and sets it to true
	bool playerMoveLeft = false; //creates a bool named playerMoveLeft and sets it to false
	bool endGameLoseMessage = false; //creates a bool named endGameLoseMessage and sets it to false;
	bool endGameWinMessage = false; //creates a bool named endGameWinMessage and sets it to false;
	bool fire = false; //creates a bool named fire and sets it to false
	

};

