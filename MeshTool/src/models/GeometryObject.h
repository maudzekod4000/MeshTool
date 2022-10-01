#ifndef GEOMETRY_OBJECT_H
#define GEOMETRY_OBJECT_H

#include <vector>

struct GeometryObject {
	std::vector<float> vertices;
	std::vector<int> triangles;
};

#endif // !GEOMETRY_OBJECT_H
