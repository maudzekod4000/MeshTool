#include "GeometryObjectParser.h"

#include <iostream>

#include "../../lib/rapidjson-1.1.0/rapidjson.h"
#include "../../lib/rapidjson-1.1.0/writer.h"
#include "../../lib/rapidjson-1.1.0/stringbuffer.h"
#include "../../lib/rapidjson-1.1.0/document.h"

void GeometryObjectParser::parse(const std::string& json)
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

const GeometryObject& GeometryObjectParser::getGeometryObject() const
{
  return geometryObject;
}
