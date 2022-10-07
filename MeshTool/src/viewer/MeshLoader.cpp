#include "MeshLoader.h"

#include <chrono>

#include "../models/Mesh.h"
#include "../files/FileReader.h"
#include "../parser/GeometryObjectBuilder.h"
#include "../models/factories/MeshFactory.h"

using namespace std::chrono;

void MeshLoader::load(const std::string& path)
{
  auto start = high_resolution_clock::now();
  
  FileReader reader;
  reader.load(path);

  GeometryObjectBuilder geometryObjBuilder;
  geometryObjBuilder.from(reader.getText());
  reader.~FileReader();

  const GeometryObject& o = geometryObjBuilder.get();
  this->indicesCount = o.trianglesIndices.size();

  this->bufferLoader = GPUBufferLoader();
  bufferLoader.init();
  bufferLoader.loadBuffers(o);

  this->mesh = MeshFactory::create(o);

  this->stats = MeshStatistics::gatherStats(this->mesh->triangles.cbegin(), this->mesh->triangles.cend());
  
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end - start);
  this->stats.loadTime = duration.count();
}

void MeshLoader::load(std::unique_ptr<Mesh> mesh)
{
  auto start = high_resolution_clock::now();

  GeometryObjectBuilder geometryObjBuilder;
  geometryObjBuilder.from(mesh);
  const GeometryObject& o = geometryObjBuilder.get();
  this->indicesCount = o.trianglesIndices.size();

  this->bufferLoader = GPUBufferLoader();
  bufferLoader.init();
  bufferLoader.loadBuffers(o);

  this->mesh = std::move(mesh);

  this->stats = MeshStatistics::gatherStats(this->mesh->triangles.cbegin(), this->mesh->triangles.cend());

  auto end = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end - start);
  this->stats.loadTime = duration.count();
}
