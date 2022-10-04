#include "MeshFactory.h"

// TODO: Maybe return const unique ptr?
std::unique_ptr<Mesh> MeshFactory::create(const GeometryObject& geometryObject)
{
	auto meshPtr = std::make_unique<Mesh>();

	// Build vertex index
	{
		const int COMPONENTS_PER_VERTEX = 3;
		const unsigned int verticesComponentsCount = geometryObject.verticesComponents.size();
		const unsigned int verticesCount = verticesComponentsCount / COMPONENTS_PER_VERTEX;

		meshPtr->verticesIndex.reserve(verticesCount);

		unsigned int vertexId = 0;
		unsigned int vertexComponentIndex = 0;

		while (vertexComponentIndex < verticesComponentsCount) {
			meshPtr->verticesIndex.emplace(
				std::piecewise_construct,
				std::make_tuple(vertexId),
				std::make_tuple(
					geometryObject.verticesComponents[vertexComponentIndex],
					geometryObject.verticesComponents[vertexComponentIndex + 1],
					geometryObject.verticesComponents[vertexComponentIndex + 2]
				)
			);

			vertexComponentIndex += COMPONENTS_PER_VERTEX;
			vertexId++;
		}
	}

	// Build triangle vector
	{
		const int COMPONENTS_PER_TRIANGLE = 3;
		const unsigned int trianglesIndicesCount = geometryObject.trianglesIndices.size();
		const unsigned int trianglesCount = trianglesIndicesCount / COMPONENTS_PER_TRIANGLE;

		meshPtr->triangles.reserve(trianglesCount);

		unsigned int triangleIndicesIndex = 0;

		while (triangleIndicesIndex < trianglesIndicesCount) {
			meshPtr->triangles.emplace_back(
				meshPtr->verticesIndex[geometryObject.trianglesIndices[triangleIndicesIndex]],
				meshPtr->verticesIndex[geometryObject.trianglesIndices[triangleIndicesIndex + 1]],
				meshPtr->verticesIndex[geometryObject.trianglesIndices[triangleIndicesIndex + 2]]
			);

			triangleIndicesIndex += COMPONENTS_PER_TRIANGLE;
		}
	}

	return meshPtr;
}
