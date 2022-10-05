#pragma once

#include "../../models/TypeDefs.h"

class Camera
{
public:
	void init(
		float fieldOfViewRadians,
		float aspectRatio,
		float nearPlane,
		float farPlane,
		const Point3D& cameraPosition,
		const Point3D& cameraTarget
	);

	const Matrix4& getProjection() const;
	const Matrix4& getView() const;
	const Point3D& getPosition() const;
	const Vector3D& getFront() const;
protected:
	Matrix4 projectionMatrix = Matrix4(1.0f);
	Matrix4 viewMatrix = Matrix4(1.0f);
	glm::vec3 cameraPosition = glm::vec3(0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 calculateUp(const Point3D& cameraTarget) const;
};
