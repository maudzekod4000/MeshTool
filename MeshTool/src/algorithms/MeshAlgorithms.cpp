#include "MeshAlgorithms.h"

std::unique_ptr<Mesh> MeshAlgorithms::subdivide2(const Mesh& mesh) {
	auto subdivMesh = std::make_unique<Mesh>();

	subdivMesh->verticesIndex = std::move(mesh.verticesIndex);

	int latestIdx = -1;

	for (auto& pair : subdivMesh->verticesIndex) {
		if (pair.first > latestIdx) {
			latestIdx = pair.first;
		}
	}

	for (auto& triangle : mesh.triangles) {
		// Find mid-point between vertices A and C on current triangle
		auto midAC = triangle.a.position + ((triangle.c.position - triangle.a.position) / 2.0f);

		// Add new vertice to map
		subdivMesh->verticesIndex[++latestIdx] = Vertex(latestIdx, midAC.x, midAC.y, midAC.z);

		// Create two new triangles

	}

	return subdivMesh;
}