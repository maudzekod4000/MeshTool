#include "MeshStatistics.h"

#include <limits>

#include "../utils/MathUtils.h"

MeshStatistics::Stats MeshStatistics::gatherStatsSeq(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end, size_t count) {
	MeshStatistics::Stats stats;
	float totalArea = 0.0f;
	float largestArea = 0.0f;
	float smallestArea = std::numeric_limits<float>::max();

	while (begin != end) {
		const Triangle& triangle = *begin;

		float area = MathUtils::calculateArea(triangle);

		if (area > largestArea) {
			largestArea = area;
			stats.largest = StatsTriangle{ triangle.a, triangle.b, triangle.c, area };
		}

		if (area < smallestArea) {
			smallestArea = area;
			stats.smallest = StatsTriangle{ triangle.a, triangle.b, triangle.c, area };
		}

		totalArea += area;

		begin++;
	}

	stats.avgArea = totalArea / count;

	return stats;
}