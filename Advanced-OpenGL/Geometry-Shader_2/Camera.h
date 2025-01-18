#pragma once

#include "Utils.h"

enum Camera_Movement
{
	FORWARD, 
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
	float pitch, yaw;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float speed;
	float fov;
public:

	Camera();
	float getFov() { return fov; }
	glm::vec3 getPos() { return cameraPos; }
	glm::vec3 getDirection() { return cameraFront; }

	void setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	glm::mat4 getViewMatrix();
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime = 1.0);
	void ProcessMouseScroll(float offset);
};

