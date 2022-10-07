#ifndef MESH_STATISTICS_H
#define MESH_STATISTICS_H

#include <vector>
#include <iterator>
#include <iostream>
#include <memory>

#include "../models/Triangle.h"
#include "../models/Mesh.h"

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
		size_t triangleCount;
		long long loadTime;
	};

	/// <summary>
	/// Gathers stats by sequentially passing through an iterator range.
	/// </summary>
	Stats gatherStatsSeq(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end);

	/// <summary>
	/// Uses all cores to gather statistics and combines them into single result.
	/// </summary>
	Stats gatherStats(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end);
};

#endif // !MESH_STATISTICS_H
