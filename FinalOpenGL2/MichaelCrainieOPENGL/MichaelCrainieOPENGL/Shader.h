#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& filename); //declaration for shader constructor that takes in a const string reference as an argument 

	void Bind(); //declaration for bind function 
	void Update(const Transform& transform, const Camera& camera); //declaration for update function that takes in a const Transform and const Camera

	std::string loadShader(const std::string& fileName); //declaration for loadShader taking in a const string reference as an argument 
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage); //declaration for checkShaderError function that takes in 2 GL unsigned ints, a bool and a const string as arguments
	GLuint createShader(const std::string& text, unsigned int type); //declaration for createShader function that takes in a const string reference and an unsigned int



	virtual ~Shader(); //declaration for ~Shader function (deconstructor)


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders
	

	enum
	{
		Transform_U,

		Num_Uniforms
	};

	GLuint program; //creates GL unsigned int named program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[Num_Uniforms]; //array of uniforms 
};

