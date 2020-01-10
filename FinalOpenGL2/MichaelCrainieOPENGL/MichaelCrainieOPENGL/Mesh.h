#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "ObjectLoader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& textureCoordinate, const glm::vec3& normal = glm::vec3(0, 0, 0)) //declaration for Vertex constructor that takes in a 2 const vec3 references and 1 const vec2 reference
	{
		this->position = position; //enables position to access it's own memory address (getter)
		this->textureCoordinate = textureCoordinate; //enables textureCoordinate to access it's own memory address (getter)
		this->normal = normal; //enables nortmal to access it's own memory address (getter)
	}

	inline glm::vec3* GetPosition() { return &position; }
	inline glm::vec2* GetTextureCoordinate() { return &textureCoordinate; }
	inline glm::vec3* GetNormal() { return &normal; }

protected:
private:
	glm::vec3 position; //vector3 named position is created
	glm::vec2 textureCoordinate; //vector2 named textureCoordinate is created
	glm::vec3 normal; //vector 3 named normal is created
};

struct Sphere
{
public:

	Sphere() {}

	Sphere(glm::vec3& pos, float radius)
	{
		this->pos = pos;
	}

	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;
};

class Mesh
{
public:
		//Mesh(Vertex* vertices, unsigned int numberOfVertices, unsigned int* indices, unsigned int numberOfIndices); //declaration of  Mesh function taking in a Vertex pointer and 3 unsigned ints as arguments (constructor)
		Mesh(const std::string& fileName); //declaration of Mesh function taking in a const string reference as an argument 

		void Draw();  //declaration for Draw function 

		virtual ~Mesh(); //declaration for ~Mesh function (deconstructor)
		void updateSphereData(glm::vec3 pos, float radius); //declaration for updateSphereData taking in a vec3 and float
		glm::vec3 getSpherePos() { return meshSphere.GetPos(); }
		float getSphereRadius() { return meshSphere.GetRadius(); }
protected:
private:
	

	void intializeMesh(const IndexedModel& model);
	

	enum
	{
		Position_VB,
		TextureCoordinate_VB,
		Normal_VB,

		Index_VB,

		Num_Buffers
	};

	Sphere meshSphere; //creates Sphere named meshSphere
	GLuint vertexArrayObject; //creates Gl unsigned int named vertexArrayObject (refers to mesh data on the GPU)
	GLuint vertextArrayBuffers[Num_Buffers]; //array of buffers
	unsigned int drawCount; //how much of the vertex array object to draw
};

