#ifndef VERTEX_H
#define VERTEX_H

#include "TypeDefs.h"

struct Vertex {
	Vertex() = default;
	Vertex(unsigned int idx, float x, float y, float z) : position(Point3D(x, y, z)), smoothNormal(Vector3D(0.0f)), idx(idx) {}

	Point3D position;
	Vector3D smoothNormal;
	unsigned int idx;
};

#endif // !VERTEX_H
