#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "src/files/FileReader.h"
#include "src/parser/GeometryObjectParser.h"
#include "src/models/factories/MeshFactory.h"
#include "src/analyser/MeshStatistics.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{
  string path;
  
  while (true) {
    cout << "Enter json file path, relative to executable: ";
    
    cin >> path;

    if (path == "q") { break; }

    FileReader reader;
    reader.load(path);

    GeometryObjectParser parser;
    parser.parse(reader.getText());
    reader.~FileReader();
    GeometryObject o = parser.getGeometryObject();

    std::unique_ptr<Mesh> mesh = MeshFactory::create(o);

    MeshStatistics::Stats meshStats = MeshStatistics::gatherStats(mesh->triangles.cbegin(), mesh->triangles.cend());

    cout << "Statistics:" << endl;
    cout << "The smallest triangle is with area " << meshStats.smallest.area << endl;
    cout << "The largest triangle is with area " << meshStats.largest.area << endl;
    cout << "The average area of all triangles is " << meshStats.avgArea << endl;
  }

  return 0;
}
