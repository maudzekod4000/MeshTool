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

int main()
{
  //TODO: Create a command prompt with the file path and print info about the mesh + statistics how long it took to calculate it.
  FileReader reader;
  reader.load("task_input/lucy.json");
  
  GeometryObjectParser parser;
  parser.parse(reader.getText());
  reader.~FileReader();
  GeometryObject o = parser.getGeometryObject();

  std::unique_ptr<Mesh> mesh = MeshFactory::create(o);

  {
    auto start = high_resolution_clock::now();
    MeshStatistics::Stats meshStats = MeshStatistics::gatherStatsSeq(mesh->triangles.cbegin(), mesh->triangles.cend());
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Sequential mesh statistics time: " << duration.count() << " and average area: " << meshStats.avgArea << endl;
  }

  {
    auto start = high_resolution_clock::now();
    auto processorCount = std::thread::hardware_concurrency();
    auto trianglesPerCore = mesh->triangles.size() / processorCount;

    MeshStatistics::Stats meshStats = MeshStatistics::gatherStats(mesh->triangles.cbegin(), mesh->triangles.cend(), trianglesPerCore);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Parallel mesh statistics time: " << duration.count() << " and average area: " << meshStats.avgArea << endl;
  }

  return 0;
}
