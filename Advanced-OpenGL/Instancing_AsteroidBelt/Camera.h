#pragma once

#include "Utils.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera {

public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;

	glm::vec3 Right;
	glm::vec3 WorldUp;

	//初始方向为X轴正向
	float Yaw;//绕Y轴旋转的角度
	float Pitch;//绕X轴旋转的角度

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f), float yaw = YAW,float pitch = PITCH)
		:Front(glm::vec3(0.0f, 0.0f, -1.0f)),MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean  constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch)
		{
			if (Pitch > 89.0)
				Pitch = 89.0;
			if (Pitch < -89.0)
				Pitch = -89.0;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		else if (direction == BACKWARD)
			Position -= Front * velocity;
		else if (direction == LEFT)
			Position -= Right * velocity;
		else if (direction == RIGHT)
			Position += Right * velocity;
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};