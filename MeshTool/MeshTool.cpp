#include <iostream>

#include "src/files/FileReader.h"
#include "src/parser/GeometryObjectParser.h"

using namespace std;
int main()
{
  FileReader reader;
  reader.load("task_input/pyramid.json");
  
  GeometryObjectParser parser;
  parser.parse(reader.getText());
  reader.~FileReader();
  GeometryObject o = parser.getGeometryObject();
  
  return 0;
}
