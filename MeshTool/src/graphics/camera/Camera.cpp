#include "Camera.h"

void Camera::init(float fieldOfViewRadians, float aspectRatio, float nearPlane, float farPlane, const Point3D& cameraPosition, const Point3D& cameraTarget)
{
	this->cameraPosition = cameraPosition;

	viewMatrix = glm::lookAt(cameraPosition, cameraTarget + cameraFront, calculateUp(cameraTarget));
	projectionMatrix = glm::perspective(fieldOfViewRadians, aspectRatio, nearPlane, farPlane);
}

const Matrix4& Camera::getProjection() const
{
	return projectionMatrix;
}

const Matrix4& Camera::getView() const
{
	return viewMatrix;
}

const Point3D& Camera::getPosition() const
{
	return cameraPosition;
}

const Vector3D& Camera::getFront() const
{
	return cameraFront;
}

glm::vec3 Camera::calculateUp(const Point3D& cameraTarget) const
{
	auto cameraDirection = glm::normalize(cameraPosition - cameraTarget);
	auto right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
	return glm::normalize(glm::cross(cameraDirection, right));
}
