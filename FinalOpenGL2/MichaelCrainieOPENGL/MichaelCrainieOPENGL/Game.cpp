#include "Game.h"
#include <iostream>
#include <string>




Game::Game() //Definition for Game function (constructor)
{
	_gameState = GameState::PLAY; //sets game to play
	display mainDisplay(); //new display called mainDisplay

}

Game::~Game() //definition for ~game function (deconstructor)
{
}

void Game::run() //definition for run function 
{
	initSystems(); //calls initSystems
	gameLoop(); //calls gameLoop
}

void Game::initSystems() //definition for initSystems function
{
	std::cout << "Destroy the monkey spaceship before it reaches earth!" << std::endl; //print line to console
	std::cout << "Hold A and D to move side to side and hold Space Bar to fire a missle" << std::endl; //print line to console
	std::cout << "The spaceship has 10 health" << std::endl; //print line to console
	mainDisplay.initDisplay(800, 600, "window"); //creates a window 800 wide, 600 tall and is named window
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav"); //load the specified wav file
	collisionSound = audioDevice.loadSound("..\\res\\CollisionSound.wav"); //load the specified wav file
	fireSound = audioDevice.loadSound("..\\res\\MissileFire.wav"); //load the specified wav file
}

void Game::gameLoop() //definition for gameLoop function
{
	while (_gameState != GameState::EXIT) //if _gameState does not equal the exit state
	{	
		drawGame(); //if the game is not in the EXIT state then call these 
		processInput();
		
	}
}

void Game::processInput()//definition for processInput function
{
	SDL_Event evnt; //creates SDL_Event named evnt
	//bool checker = true;
	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
		{
			switch (evnt.key.keysym.sym)
			{
			case SDLK_a: //if the a key is pressed perform the following actions
			{	
					std::cout << "Move Left" << std::endl;
					playerXValue += 0.45f;
					break;			
			}
			case SDLK_d: //if the d key is pressed perform the following actions 
			{				
					std::cout << "Move Right" << std::endl;
					playerXValue -= 0.45f;
					break;			
			}

			case SDLK_SPACE: //if the space key is pressed perform the following actions 
			{
				if (fire == false) //if fire is false perform the following actions 
				{
					std::cout << "Fire" << std::endl;
					fire = true;
					break;
				}

			}
			}

		}
		break;
		}
	}
}




		

		
	

	




bool Game::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad) //definition for collision function that takes in 2 glm::vec3's and 2 floats
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z)); //calculates distance between 2 meshes

	if (distance < (m1Rad + m2Rad)) //if distance is less that the combined radius of the 2 meshes perform the following actions
	{
		std::cout << "Missile Hit" << std::endl;
		std::cout << "Collision sound may be low but does play" << std::endl;
		std::cout << "Monkey spaceship health is " << health - 1 << std::endl;
		playAudio(collisionSound, m1Pos);
		health -= 1;
		fire = false;
		missileYValue = -3.55f;
		return true;
	}

	else
	{
		
		return false;
	}


}

void Game::playAudio(unsigned int Source, glm::vec3 pos) //definition for playAudio function that takes in an unsigned int and a glm::vec3 as arguments
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state) //if the specified audio is not already playing play it 
	{
		audioDevice.playSound(Source, pos);
	}
}


void Game::drawGame() //defintion  for drawGame function
{
	
	

	/*Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0, 0.5, 0),  glm::vec2(0.5,1.0)),
							Vertex(glm::vec3(0.5, -0.5, 0),  glm::vec2(1.0, 0.0)) };*/

	//unsigned int indices[] = { 0, 1, 2 };

	//Mesh mesh("..\\res\\Colt.obj"); //vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0])); //size calcuated by number of bytes of an array / no bytes of one element
	Mesh mesh2("..\\res\\monkey3.obj");
	Mesh mesh("..\\res\\colt3.obj");
	Mesh mesh3("..\\res\\betterShuriken.obj");
	Mesh mesh5("..\\res\\Rocket2.obj"); //creates the meshes by loading in the specified obj files
	Shader shader("..\\res\\basicShader"); //new shader
	Texture texture("..\\res\\glass.jpg");
	Texture texture2("..\\res\\gold2.png");
	Texture texture3("..\\res\\Carbon.jfif");
	Texture texture4("..\\res\\bricks.jpg");
	Texture texture5("..\\res\\MissileTex.jpg"); //creates the textures by loading in the specified image files
	Camera camera(glm::vec3(0,0,-10), 70.0f, (float)800/(float)600, 0.01f, 1000.0f); //creates and sets coordinates for the camera 
	Transform transform;
	Transform transform2;
	Transform transform3;
	Transform transform4;
	Transform transform5; //creates the transforms
	//char key = _getch();
	//int value = key;
	
	

	transform4.SetPosition(glm::vec3(-3.5f, 2.0f, 0.0f));
	transform4.SetRotation(glm::vec3(0.0f, 45.0f, 0));
	//transform4.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));

	float counter = 0.0f;
	//transform3.SetRotation(glm::vec3(90.0f, 90.0f, 0));
	
	while (!mainDisplay.isClosed())
	{
		mainDisplay.clear(0.45f, 0.3f, 0.9f, 1.0f); //calls the clear function
		playAudio(backGroundMusic, glm::vec3(0.0f, 0.0f, 0.0f)); //plays background music
		float sinCounter = sinf(counter); //used to give rotation to meshes
		float cosCounter = cosf(counter); //used to give rotation to meshes
		//std::cout << checking << std::endl;
		transform.GetPostition().x = sinCounter;
		transform.GetPostition().z = cosCounter;
		transform.GetRotation().z = counter * 5;
		transform.GetRotation().y = counter * 5;
		transform.GetRotation().x = counter * 5;
		transform2.GetPostition().x = sinCounter;
		transform2.GetPostition().z = cosCounter;
	//	transform2.GetRotation().z = counter * 5;
	   // transform2.GetRotation().y = counter * 5;
	//	transform2.GetRotation().x = counter * 5;
		transform3.GetPostition().x = sinCounter;
		transform3.GetPostition().z = cosCounter;
	//	transform3.GetRotation().z = counter * 5;
	//	transform3.GetRotation().y = counter * 5;
		transform3.GetRotation().x = counter * 20;
		//transform3.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		
		if (moveRight == true)
		{
			monkeyHeadXValue -= 0.004f; //if moveRight is true decrement the variable 
		}

		if (moveRight == false)
		{
			monkeyHeadXValue += 0.004f; //if moveRight is true increment the variable
		}

		if (monkeyHeadXValue >= 4.0) //if variable is greater than or equal to 4.0 perform actions
		{
			moveRight = true;
			monkeyHeadYValue -= 0.5f;
		}

		if (monkeyHeadXValue <= -4.0) //if variable is less than or equal to negative 4.0 perform actions
		{
			moveRight = false;
			monkeyHeadYValue -= 0.5f;
		}

		if (monkeyHeadYValue <= -1.50f && (endGameLoseMessage == false)) //if conditions met perform actions
		{
			mesh.~Mesh(); 
			mesh5.~Mesh(); //call deconstructor on both of these meshes			
			std::cout << "You failed to save earth, the monkeys have won" << std::endl;
			endGameLoseMessage = true;
			//monkeyHeadYValue += 200.0f;
			playerXValue += 200.0f;
		}

		
		if (health <= 0 && (endGameWinMessage == false)) //if conditions met perform actions
		{ 
			std::cout << "You stopped the space monkey invasion!" << std::endl;
			mesh2.~Mesh(); //deconstruct mesh
			endGameWinMessage = true;
			monkeyHeadYValue += 200.0f;
		}

		if (fire == true) //if condition met perform actions 
		{
			missileYValue += 0.03f;	
			playAudio(fireSound, glm::vec3(0, 0, 0));
		}

		if (missileYValue >= 5.0f) //if condition met perform actions
		{
			fire = false;
			std::cout << "Missile missed" << std::endl;
			missileYValue = -3.55f;
		}

		
		transform.SetPosition(glm::vec3(monkeyHeadXValue, monkeyHeadYValue, 0.0f));
		transform2.SetPosition(glm::vec3(playerXValue, playerYvalue, playerZValue));
		transform2.SetRotation(glm::vec3(29.85f, 2.0f, 0.0f));
		transform2.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		transform3.SetPosition(glm::vec3(-3.5f, -2.0f, 0.0f));
		transform4.SetPosition(glm::vec3(playerXValue - 0.25f, missileYValue, 0));
		transform4.SetScale(glm::vec3(0.5f, 0.5f, 0.5f)); //setting position, rotation and scale for different transforms
	//	transform5.SetPosition(glm::vec3(0, 0, 0));

		texture5.Bind(0);
		shader.Bind();
		shader.Update(transform4, camera);
		mesh5.Draw();
		mesh5.updateSphereData(transform4.GetPostition(), 0.62f); //this section loads in the mesh with the specified texture at the transform given to it on our camera then draws it with its collision sphere

		
		
		texture.Bind(0);
		shader.Bind();
		shader.Update(transform, camera);
		mesh2.Draw();
		mesh2.updateSphereData(transform.GetPostition(), 0.62f); //this section loads in the mesh with the specified texture at the transform given to it on our camera then draws it with its collision sphere

		texture2.Bind(0);
		shader.Update(transform2, camera);
		mesh.Draw();
		mesh.updateSphereData(transform2.GetPostition(), 0.62f);//this section loads in the mesh with the specified texture at the transform given to it on our camera then draws it with its collision sphere

		texture3.Bind(0);
		shader.Update(transform3, camera);
		mesh3.Draw();
		mesh3.updateSphereData(transform3.GetPostition(), 0.62f); //this section loads in the mesh with the specified texture at the transform given to it on our camera then draws it with its collision sphere

		//texture3.Bind(0);
		//shader.Update(transform4, camera);
		//mesh4.Draw();
		collision(mesh5.getSpherePos(), mesh5.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius()); //if these meshes collide perform the actions in the collision function
		processInput(); //calls processInput function
		mainDisplay.update(); //calls the mainDisplay's update function
		counter += 0.0001f;
		

		
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();
	
}