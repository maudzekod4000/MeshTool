#ifndef MESH_STATISTICS_H
#define MESH_STATISTICS_H

#include <vector>
#include <iterator>

#include "../models/Triangle.h"

namespace MeshStatistics {
	struct StatsTriangle {
		Vertex a;
		Vertex b;
		Vertex c;
		float area;
	};

	struct Stats {
		StatsTriangle smallest;
		StatsTriangle largest;
		float avgArea;
	};

	Stats calculate(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end, size_t count);
}

#endif // !MESH_STATISTICS_H
