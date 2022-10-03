#include "MeshFactory.h"

// TODO: Maybe return const unique ptr?
std::unique_ptr<Mesh> MeshFactory::create(const GeometryObject& geometryObject)
{
	auto meshPtr = std::make_unique<Mesh>();

	// Build vertex index
	unsigned int vertexId = 0;
	unsigned int vertexComponentIndex = 0;
	unsigned int verticesSize = geometryObject.vertices.size();

	return std::unique_ptr<Mesh>();
}
