#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& filename) //definition for Texture function taking in a const string reference as an argument (constructor)
{
	int height, width, numberOfComponents; //info to pass into stbi 
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numberOfComponents, 4); //loads texture data

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for the texture named " << filename << std::endl; //error message if imageData is NULL
	}

	glGenTextures(1, &texture); //generates space for texture
	glBindTexture(GL_TEXTURE_2D, texture); //any operation that would effect a texture will effect this one 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //instructs openGL what to do if pixel is outwith the texture bounds (one line is height one line is width)


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //instructs openGL what do if texture takes up less or more pixels than the resolution

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //sends texture to the gpu 


	stbi_image_free(imageData);//deletes texture data when no longer in use 
}

Texture::~Texture() //definition for ~Texture function (deconstuctor)
{
	glDeleteTextures(1, &texture); //deletes the texture
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); //keeps unit within desired range

	glActiveTexture(GL_TEXTURE0 + unit); //specifies which texture openGL will work with 
	glBindTexture(GL_TEXTURE_2D, texture); //any operation that uses a texture will use this one 
}
	
