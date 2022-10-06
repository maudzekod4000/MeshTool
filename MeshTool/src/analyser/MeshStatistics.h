#ifndef MESH_STATISTICS_H
#define MESH_STATISTICS_H

#include <vector>
#include <iterator>
#include <iostream>

#include "../models/Triangle.h"

namespace MeshStatistics {
	static struct StatsTriangle {
		Vertex a;
		Vertex b;
		Vertex c;
		float area;
	};

	static struct Stats {
		MeshStatistics::StatsTriangle smallest;
		MeshStatistics::StatsTriangle largest;
		float avgArea;
	};

	/// <summary>
	/// Gathers stats about smallest, largest and average area of all triangles in a mesh.
	/// Iterates elements sequentially and is used to calculate stats when number of elements in the iterator range
	/// falls below the sensible lower limit for further division and thread creation.
	/// </summary>
	/// <returns>Statistics about the mesh. See MeshStatistics::Stats.</returns>
	Stats gatherStatsSeq(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end);

	Stats gatherStats(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end);
};

#endif // !MESH_STATISTICS_H
