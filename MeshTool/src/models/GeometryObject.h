#ifndef GEOMETRY_OBJECT_H
#define GEOMETRY_OBJECT_H

#include <vector>

struct GeometryObject {
	std::vector<float> verticesComponents;
	std::vector<int> trianglesIndices;
};

#endif // !GEOMETRY_OBJECT_H
