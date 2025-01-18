#include "Camera.h"

Camera::Camera()
{
	cameraPos = glm::vec3(0.0, 0.0, 25.0);
	cameraFront = glm::vec3(0.0, 0.0, -1.0);
	cameraUp = glm::vec3(0.0, 1.0, 0.0);

	pitch = 0.0;
	yaw = 0.0;//-3.1515926;
	fov = 45.0;

	speed = 0.05;
}

void Camera::setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	cameraPos = eye;
	cameraFront = center - cameraPos;
	cameraUp = up;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessMouseScroll(float offset)
{
	fov -= offset;
	if (fov < 1.0)
		fov = 1.0;
	if (fov > 85.0)
		fov = 85.0;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	float sensitivity = 0.005;
	xoffset *= sensitivity;
	yoffset *= sensitivity;


	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0)
			pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(pitch)*sin(yaw);
	front.y = sin(pitch);
	front.z = -cos(pitch)*cos(yaw);

	cameraFront = glm::normalize(front);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	speed *= deltaTime;
	if(direction == Camera_Movement::FORWARD)
		cameraPos += speed * cameraFront;
	else if(direction == Camera_Movement::BACKWARD)
		cameraPos -= speed * cameraFront;
	else if(direction == Camera_Movement::LEFT)
		cameraPos += speed * glm::normalize(glm::cross(cameraUp, cameraFront));
	else if(direction == Camera_Movement::RIGHT)
		cameraPos -= speed * glm::normalize(glm::cross(cameraUp, cameraFront));
}