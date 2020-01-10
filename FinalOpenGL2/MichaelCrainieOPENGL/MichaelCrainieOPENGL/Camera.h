#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
class Camera
{
public:
	Camera(const glm::vec3& position, float fov, float aspect, float near, float far) //Definition for Camera function that takes in a const glm::vec3 reference and 4 floats as arguments
	{
		_perspective = glm::perspective(fov, aspect, near, far); //sets value of _perspective
		_position = position; //sets value of _position 
		_forwardVector = glm::vec3(0, 0, 1); //sets value of _forward vector 
		_upVector = glm::vec3(0, 1, 0); //sets value of _upVector 
		height = 800.0f; //sets value of height 
		width = 600.0f; //sets value of width
	}

	inline glm::mat4 GetViewProjection() const
	{
		return _perspective * glm::lookAt(_position, _position + _forwardVector, _upVector); //calculates the view projection matrix
	}
protected:
private:
	glm::mat4 _perspective; //creates a variable of type glm::mat4 named _perspective
	glm::vec3 _position; //creates a variable of type glm::vec3 named _position 
	glm::vec3 _forwardVector; //creates a variable of type glm::vec3 named _forwardVector 
	glm::vec3 _upVector; //creates a variable of type named _upVector 
	float height; //creates a variable of type float named height 
	float width; //creates a variable of type float named width 
};