#include "FPSCamera.h"

#include <iostream>

void FPSCamera::init(float fieldOfViewRadians, float aspectRatio, float nearPlane, float farPlane, const Point3D& cameraPosition, const Point3D& cameraTarget, float screenWidth, float screenHeight)
{
	Camera::init(fieldOfViewRadians, aspectRatio, nearPlane, farPlane, cameraPosition, cameraTarget);
	this->lastX = screenWidth / 2;
	this->lastY = screenHeight / 2;
	this->pitch = 1.0f;
	this->yaw = 89.0f;
	this->cameraTarget = cameraTarget;
}

void FPSCamera::moveForward()
{
	cameraPosition += cameraSpeed * cameraFront;
	calculateView();
}

void FPSCamera::moveBackward()
{
	cameraPosition -= cameraSpeed * cameraFront;
	calculateView();
}

void FPSCamera::moveLeft()
{
	cameraPosition -= cameraSpeed * glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	calculateView();
}

void FPSCamera::moveRight()
{
	cameraPosition += cameraSpeed * glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	calculateView();
}

void FPSCamera::onMouseMove(double xpos, double ypos)
{
	if (firstMouseEnter)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouseEnter = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cameraFront = glm::normalize(glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	));
	
	calculateView();
}

void FPSCamera::calculateView()
{
	viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
}
