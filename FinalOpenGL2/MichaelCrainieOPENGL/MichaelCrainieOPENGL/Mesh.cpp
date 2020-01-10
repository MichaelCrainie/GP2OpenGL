#include "Mesh.h"
#include "ObjectLoader.h"
#include <vector>

Mesh::Mesh(const std::string& fileName) //definition of Mesh function taking in a const string reference as an argument
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	intializeMesh(model);
	Sphere meshSphere();
}


/*Mesh::Mesh(Vertex* vertices, unsigned int numberOfVertices, unsigned int* indices, unsigned int numberOfIndices)
{
	IndexedModel model; //creates variable of type IndexedModel named model 

	for (unsigned int i = 0; i < numberOfVertices; i++) //for each numberOfVertices 
	{
		model.positions.push_back(*vertices[i].GetPosition()); 
		model.texCoords.push_back(*vertices[i].GetTextureCoordinate());
		model.normals.push_back(*vertices[i].GetNormal()); //push back is used to push these elements into a vector from the back
	}

	for (unsigned int i = 0; i < numberOfIndices; i++) //for each numberOfIndices
	{
		model.indices.push_back(indices[i]); //push back is used to push these elements into a vector from the back
	}

	intializeMesh(model);
	//drawCount = numberOfIndices;
	/*glGenVertexArrays(1, &vertexArrayObject); //creates space for vertex array
	glBindVertexArray(vertexArrayObject); //any operation that would effect a vertex array object will effect this one 

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textureCoordinates;

	positions.reserve(numberOfVertices);
	textureCoordinates.reserve(numberOfVertices); //means openGL does not need to reallocate data

	for (unsigned int i = 0; i < numberOfVertices; i++)
	{
		positions.push_back(*vertices[i].GetPosition());
		textureCoordinates.push_back(*vertices[i].GetTextureCoordinate());
	}
	

	glGenBuffers(Num_Buffers, vertextArrayBuffers); //enables us to get data on the gpu and write to it 
	glBindBuffer(GL_ARRAY_BUFFER, vertextArrayBuffers[Position_VB]); //any operation that would effect a buffer will now effect this buffer
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW); //puts position data into the array

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //lets openGL have data on Gpu and enables it to draw it
	
	glBindBuffer(GL_ARRAY_BUFFER, vertextArrayBuffers[TextureCoordinate_VB]); //any operation that would effect a buffer will now effect this buffer
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(textureCoordinates[0]), &textureCoordinates[0], GL_STATIC_DRAW); //puts texture data into the array
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //lets openGL have data on Gpu and enables it to draw it

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertextArrayBuffers[Index_VB]); //any operation that would effect a buffer will now effect this buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW); //puts texture data into the array

	glBindVertexArray(0); //any operation that would effect a vertex array object will not only effect this one 
	
}*/

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); //deletes vertex array object
}

void Mesh::intializeMesh(const IndexedModel& model)
{
	drawCount = model.indices.size(); //draw count is equal to the number of indices the model has
	glGenVertexArrays(1, &vertexArrayObject); //creates space for vertex array
	glBindVertexArray(vertexArrayObject); //any operation that would effect a vertex array object will effect this one

	glGenBuffers(Num_Buffers, vertextArrayBuffers); //enables us to get data on the gpu and write to it 
	glBindBuffer(GL_ARRAY_BUFFER, vertextArrayBuffers[Position_VB]); //any operation that would effect a buffer will now effect this buffer
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //gets the size of the data going to the gpu for positions and GL_STATIC_DRAW tells it where to store it

	glEnableVertexAttribArray(0); //enables first attribute in the array 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //accesses first attrib in the array, 3 components and defined as floats 

	glBindBuffer(GL_ARRAY_BUFFER, vertextArrayBuffers[TextureCoordinate_VB]); //any operation that would effect a buffer will now effect this buffer
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //gets the size of the data going to the gpu for texCoords and GL_STATIC_DRAW tells it where to store it

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //accesses second attribute in the array, 2 components and defined as floats 

	glBindBuffer(GL_ARRAY_BUFFER, vertextArrayBuffers[Normal_VB]); //any operation that would effect a buffer will now effect this buffer
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW); //gets the size of the data going to the gpu for normals and GL_STATIC_DRAW tells it where to store it

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0); //accesses third attribute in the array, 3 components and defined as floats 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertextArrayBuffers[Index_VB]); //any operation that would effect a buffer will now effect this buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //gets the size of the data going to the gpu for indices and GL_STATIC_DRAW tells it where to store it

	glBindVertexArray(0); //any operation that would effect a vertex array object will not only effect this one 
}


void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject); //any operation that would effect a vertex array object will effect this one 

	//glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0); //specifies what kind of shapes to render and how many 
	glBindVertexArray(0);

	
}

void Mesh::updateSphereData(glm::vec3 pos, float radius) //declaration for updateSphereData function that takes in a glm::vec3 and a float as arguments 
{
	meshSphere.SetPos(pos); //set pos
	meshSphere.SetRadius(radius); //set radius
}
