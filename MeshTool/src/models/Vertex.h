#ifndef VERTEX_H
#define VERTEX_H

#include "TypeDefs.h"

struct Vertex {
	Vertex() = default;
	Vertex(float x, float y, float z) : position(Point3D(x, y, z)), smoothNormal(Vector3D(0.0f)) {}

	Point3D position;
	Vector3D smoothNormal;
};

#endif // !VERTEX_H
