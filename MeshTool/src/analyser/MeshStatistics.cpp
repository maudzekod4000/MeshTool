#include "MeshStatistics.h"

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
	if (std::distance(begin, end) < parallelLowLimit) {
		return gatherStatsSeq(begin, end);
	}

	size_t mid = std::distance(begin, end) / 2;

	std::promise<MeshStatistics::Stats> leftPromise;

	auto leftJob = std::thread([&] {
		leftPromise.set_value(gatherStats(begin, begin + mid, parallelLowLimit));
	});

	std::promise<MeshStatistics::Stats> rightPromise;

	auto rightJob = std::thread([&] {
		rightPromise.set_value(gatherStats(begin + mid, end, parallelLowLimit));
	});

	auto leftFuture = leftPromise.get_future();
	auto rightFuture = rightPromise.get_future();

	MeshStatistics::Stats leftStats = leftFuture.get();
	MeshStatistics::Stats rightStats = rightFuture.get();

	leftJob.join();
	rightJob.join();

	MeshStatistics::Stats combinedStats;

	combinedStats.largest = leftStats.largest.area > rightStats.largest.area ? leftStats.largest : rightStats.largest;
	combinedStats.smallest = leftStats.smallest.area < rightStats.smallest.area ? leftStats.smallest : rightStats.smallest;
	combinedStats.avgArea = (leftStats.avgArea + rightStats.avgArea) / 2.0f;

	return combinedStats;
}
