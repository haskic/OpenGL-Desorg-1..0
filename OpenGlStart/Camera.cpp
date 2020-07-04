#include "Camera.h"

glm::mat4 Camera::getCameraMatrix()
{

	return glm::lookAt(glm::vec3(x,y,z),glm::vec3(toX,toY,toZ),headVector);
}

