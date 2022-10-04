#include <iostream>
#include <memory>

#include "src/files/FileReader.h"
#include "src/parser/GeometryObjectParser.h"
#include "src/models/factories/MeshFactory.h"

using namespace std;
int main()
{
  //TODO: Create a command prompt with the file path and print info about the mesh + statistics how long it took to calculate it.
  FileReader reader;
  reader.load("task_input/pyramid.json");
  
  GeometryObjectParser parser;
  parser.parse(reader.getText());
  reader.~FileReader();
  GeometryObject o = parser.getGeometryObject();

  std::unique_ptr<Mesh> mesh = MeshFactory::create(o);
  
  return 0;
}
