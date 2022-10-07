#include "GeometryObjectBuilder.h"

#include <iostream>

#include "../../lib/rapidjson-1.1.0/rapidjson.h"
#include "../../lib/rapidjson-1.1.0/writer.h"
#include "../../lib/rapidjson-1.1.0/stringbuffer.h"
#include "../../lib/rapidjson-1.1.0/document.h"

void GeometryObjectBuilder::from(const std::string& json)
{
  using namespace rapidjson;

  Document d;
  d.Parse(json.c_str());

  Value& vertices = d["geometry_object"]["vertices"];
  size_t verticesSize = vertices.GetArray().Size();
  geometryObject.verticesComponents.reserve(verticesSize);
  
  for (auto& jsonArrVal : vertices.GetArray()) {
    geometryObject.verticesComponents.push_back(jsonArrVal.GetFloat());
  }

  Value& triangles = d["geometry_object"]["triangles"];
  size_t trianglesSize = triangles.GetArray().Size();
  geometryObject.trianglesIndices.reserve(trianglesSize);

  for (auto& jsonArrVal : triangles.GetArray()) {
    geometryObject.trianglesIndices.push_back(jsonArrVal.GetInt());
  }
}

void GeometryObjectBuilder::from(std::unique_ptr<Mesh>& mesh)
{
  geometryObject.trianglesIndices.reserve(mesh->triangles.size() * 3);

  for (auto& triangle : mesh->triangles) {
    geometryObject.trianglesIndices.push_back(triangle.a.idx);
    geometryObject.trianglesIndices.push_back(triangle.b.idx);
    geometryObject.trianglesIndices.push_back(triangle.c.idx);
  }

  geometryObject.verticesComponents.reserve(mesh->verticesIndex.size() * 3);

  for (size_t idx = 0; idx < mesh->verticesIndex.size(); idx++) {
    Vertex& vertex = mesh->verticesIndex[idx];
    geometryObject.verticesComponents.push_back(vertex.position.x);
    geometryObject.verticesComponents.push_back(vertex.position.y);
    geometryObject.verticesComponents.push_back(vertex.position.z);
  }
}

const GeometryObject& GeometryObjectBuilder::get() const
{
  return geometryObject;
}
