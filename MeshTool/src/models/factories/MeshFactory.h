#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include <memory>

#include "../Mesh.h"
#include "../GeometryObject.h"

/// <summary>
/// A collection of methods used to create instance of a Mesh.
/// </summary>
namespace MeshFactory {
	std::unique_ptr<Mesh> create(const GeometryObject& geometryObject);
}

#endif // !MESH_FACTORY_H
