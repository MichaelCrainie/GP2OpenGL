#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& filename) //definition of Shader function taking in a const string (Constructor)
{
	program = glCreateProgram(); // create shader program 
	shaders[0] = createShader(loadShader(filename + ".vert"), GL_VERTEX_SHADER); // create vertex shader
	shaders[1] = createShader(loadShader(filename + ".frag"), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++) //for each NUM_SHADERS
	{
		glAttachShader(program, shaders[i]); //add all our shaders to the program
	}

	glBindAttribLocation(program, 0, "position"); //binds the attibute of position
	glBindAttribLocation(program, 1, "texCoord"); //binds the attibute of texCoord
	glBindAttribLocation(program, 2, "normal"); //binds the attibute of normal

	glLinkProgram(program); //create executables that will run on the GPU shaders
	checkShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // check for error

	glValidateProgram(program); //validate the program
	checkShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid"); //check the entire program is valid

	uniforms[Transform_U] = glGetUniformLocation(program, "transform"); //gives access to transform uniform 
}


Shader::~Shader() //definition for ~Shader function (destructor)
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++) //for each NUM_SHADERS
	{
		glDetachShader(program, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the shaders
	}
	glDeleteProgram(program); // delete the program
}

void Shader::Bind() //definition for Bind function
{
	glUseProgram(program); //any function that references a program will use this program
}

void Shader::Update(const Transform& transform, const Camera& camera) //definition for Update fucntion taking in a const Transform and const Camera as arguments
{
	glm::mat4 MVP = camera.GetViewProjection() * transform.GetModel(); //creates model view projection matrix
	glUniformMatrix4fv(uniforms[Transform_U], 1, GL_FALSE, &MVP[0][0]); //updates uniforms 
}

GLuint Shader::createShader(const std::string& text, unsigned int type) //definition for createShader function taking in a const string and unsigned int as arguments 
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader not created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

std::string Shader::loadShader(const std::string& fileName) //declaration for loadShader taking in a const string as an argument (Only used to load in text file from hard drive)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl; //displays error message if unable to load text file from hard drive
	}

	return output;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) //declaration for checkShaderError message taking in a 2 GL unsigned ints, a bool and a const string as arguments (Finds and generates error messages for shaders)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
