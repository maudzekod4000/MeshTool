#include "MeshLoader.h"

#include "../models/Mesh.h"
#include "../files/FileReader.h"
#include "../parser/GeometryObjectBuilder.h"
#include "../models/factories/MeshFactory.h"

void MeshLoader::load(const std::string& path)
{
  FileReader reader;
  reader.load(path);

  GeometryObjectBuilder geometryObjBuilder;
  geometryObjBuilder.parse(reader.getText());
  reader.~FileReader();

  GeometryObject o = geometryObjBuilder.getGeometryObject();
  this->indicesCount = o.trianglesIndices.size();

  this->bufferLoader = GPUBufferLoader();
  bufferLoader.init();
  bufferLoader.loadBuffers(o);

  this->mesh = MeshFactory::create(o);

  this->stats = MeshStatistics::gatherStats(this->mesh->triangles.cbegin(), this->mesh->triangles.cend());
}

void MeshLoader::load(std::unique_ptr<Mesh> mesh)
{
  GeometryObjectBuilder geometryObjBuilder;
  geometryObjBuilder.fromMesh(mesh);
  GeometryObject o = geometryObjBuilder.getGeometryObject();
  this->indicesCount = o.trianglesIndices.size();

  this->bufferLoader = GPUBufferLoader();
  bufferLoader.init();
  bufferLoader.loadBuffers(o);

  this->mesh = std::move(mesh);

  this->stats = MeshStatistics::gatherStats(this->mesh->triangles.cbegin(), this->mesh->triangles.cend());
}
