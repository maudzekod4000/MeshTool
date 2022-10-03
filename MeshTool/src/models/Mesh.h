#ifndef MESH_H
#define MESH_H

#include <unordered_map>
#include <vector>

#include "TypeDefs.h"
#include "Triangle.h"

struct Mesh {
	std::unordered_map<int, Vertex> verticesIndex;
	std::vector<Triangle> triangles;
};

#endif // !MESH_H
