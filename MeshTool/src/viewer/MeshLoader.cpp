#include "MeshLoader.h"

#include "../models/Mesh.h"
#include "../files/FileReader.h"
#include "../parser/GeometryObjectParser.h"
#include "../models/factories/MeshFactory.h"

void MeshLoader::load(const std::string& path)
{
  FileReader reader;
  reader.load(path);

  GeometryObjectParser parser;
  parser.parse(reader.getText());
  reader.~FileReader();

  GeometryObject o = parser.getGeometryObject();
  this->indicesCount = o.trianglesIndices.size();

  this->bufferLoader = GPUBufferLoader();
  bufferLoader.init();
  bufferLoader.loadBuffers(o);

  this->mesh = MeshFactory::create(o);

  this->stats = MeshStatistics::gatherStats(this->mesh->triangles.cbegin(), this->mesh->triangles.cend());
}
