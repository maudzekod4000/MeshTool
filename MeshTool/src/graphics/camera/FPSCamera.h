#pragma once

#include "Camera.h"

class FPSCamera : public Camera {
public:
	void init(
		float fieldOfViewRadians,
		float aspectRatio,
		float nearPlane,
		float farPlane,
		const Point3D& cameraPosition,
		const Point3D& cameraTarget,
		float screenWidth,
		float screenHeight
	);

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void onMouseMove(double xpos, double ypos);
protected:
	glm::vec3 cameraTarget;
	float lastX{};
	float lastY{};
	float yaw{};
	float pitch{};
	float sensitivity = 0.1f;
	float cameraSpeed = 0.04f;
	bool firstMouseEnter = true;

	void calculateView();
};