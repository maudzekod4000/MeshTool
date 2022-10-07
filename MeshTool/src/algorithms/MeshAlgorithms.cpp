#include "MeshAlgorithms.h"

#include "../utils/MathUtils.h"

std::unique_ptr<Mesh> MeshAlgorithms::subdivide2(const Mesh& mesh) {
	auto subdivMesh = std::make_unique<Mesh>();

	subdivMesh->verticesIndex = std::move(mesh.verticesIndex);

	int latestIdx = subdivMesh->verticesIndex.size() - 1;

	for (auto& triangle : mesh.triangles) {
		// Find mid-point between vertices A and C on current triangle
		auto midAC = triangle.a.position + ((triangle.c.position - triangle.a.position) / 2.0f);

		// Add new vertice to map
		latestIdx++;
		subdivMesh->verticesIndex[latestIdx] = Vertex(latestIdx, midAC.x, midAC.y, midAC.z);
		subdivMesh->verticesIndex[latestIdx].smoothNormal = MathUtils::calculateSurfaceGeometricNormal(
			subdivMesh->verticesIndex[latestIdx].position,
			triangle.a.position,
			triangle.b.position
		);

		// Create two new triangles
		subdivMesh->triangles.emplace_back(
			subdivMesh->verticesIndex[latestIdx],
			subdivMesh->verticesIndex[triangle.a.idx],
			subdivMesh->verticesIndex[triangle.b.idx]
		);
		subdivMesh->triangles.emplace_back(
			subdivMesh->verticesIndex[latestIdx],
			subdivMesh->verticesIndex[triangle.c.idx],
			subdivMesh->verticesIndex[triangle.b.idx]
		);
	}

	return subdivMesh;
}