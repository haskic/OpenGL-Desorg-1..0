#include <glm.hpp>
#include <vec4.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/string_cast.hpp>
#include <mat4x4.hpp>
#pragma once
class Camera
{
public:
	float x;
	float y;
	float z;
	float toX;
	float toY;
	float toZ;
	glm::vec3 headVector;

	Camera()
	{

	}
	Camera(float xPos, float yPos, float zPos, float toXPos, float toYPos, float toZPos, glm::vec3 head) {
		x = xPos;
		y = yPos;
		z = zPos;
		toX = toXPos;
		toY = toYPos;
		toZ = toZPos;
		headVector = head;

	}
	glm::mat4 getCameraMatrix();
};

