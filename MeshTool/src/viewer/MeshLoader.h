#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <string>
#include <iostream>
#include <memory>

#include "../statistics/MeshStatistics.h"
#include "GPUBufferLoader.h"

struct MeshLoader {
	/// <summary>
	/// Entrypoint for mesh processing.
	/// 
	/// 1. Loads the json file.
	/// 2. Calls method to transform the json into a GeometryObject for easy processing.
	/// 3.1 Calls method to load to GPU buffer with mesh data for display.
	/// 3.2 Calls method to transform GeometryObject into Mesh for easier statistic analysis.
	/// 4. Calls method to perform analysis on the mesh.
	/// </summary>
	/// <param name="path">File path to mesh json file.</param>
	void load(const std::string& path);

	void load(std::unique_ptr<Mesh> mesh);
	
	size_t indicesCount;
	MeshStatistics::Stats stats;
	std::unique_ptr<Mesh> mesh;
private:
	GPUBufferLoader bufferLoader;
};

#endif // !MESH_LOADER_H
