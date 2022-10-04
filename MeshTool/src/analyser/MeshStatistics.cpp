#include "MeshStatistics.h"

#include <iostream>
#include <limits>
#include <future>
#include <thread>

#include "../utils/MathUtils.h"

MeshStatistics::Stats MeshStatistics::gatherStatsSeq(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end) {
	size_t count = std::distance(begin, end);
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

MeshStatistics::Stats MeshStatistics::gatherStats(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end, size_t parallelLowLimit)
{
	if (std::distance(begin, end) < parallelLowLimit + 1) {
		return gatherStatsSeq(begin, end);
	}

	size_t mid = std::distance(begin, end) / 2;

	MeshStatistics::Stats leftStats;

	auto leftJob = std::thread([&] {
		leftStats = gatherStats(begin, begin + mid, parallelLowLimit);
	});

	MeshStatistics::Stats rightStats;

	auto rightJob = std::thread([&] {
		rightStats = gatherStats(begin + mid, end, parallelLowLimit);
	});

	leftJob.join();
	rightJob.join();

	MeshStatistics::Stats combinedStats;

	combinedStats.largest = leftStats.largest.area > rightStats.largest.area ? leftStats.largest : rightStats.largest;
	combinedStats.smallest = leftStats.smallest.area < rightStats.smallest.area ? leftStats.smallest : rightStats.smallest;
	combinedStats.avgArea = (leftStats.avgArea + rightStats.avgArea) / 2.0f;

	return combinedStats;
}
