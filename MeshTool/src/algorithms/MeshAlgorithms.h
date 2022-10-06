#ifndef MESH_ALGO_H
#define MESH_ALGO_H

#include <memory>

#include "../models/Mesh.h"

namespace MeshAlgorithms {
	std::unique_ptr<Mesh> subdivide2(const Mesh& mesh);
}

#endif // !MESH_ALGO_H
