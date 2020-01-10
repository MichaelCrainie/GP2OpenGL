#pragma once
#include <string>
#include <GL/glew.h>
class Texture
{
public:
	Texture(const std::string& filename); //declaration for Texture function that takes in a const string reference as an argument 

	void Bind(unsigned int unit); //declaration for Bind function taking in an unsigned int as an argument (sets openGL to use the selected texture to bind)

	virtual ~Texture(); //declaration for ~Texture function (deconstructor)
protected:
private:
	

	GLuint texture; //creates variable named texture that is of type GL unsigned int 
};

