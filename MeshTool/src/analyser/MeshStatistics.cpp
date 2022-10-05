#include "MeshStatistics.h"

#include <iostream>
#include <limits>
#include <future>
#include <thread>

#include "../utils/MathUtils.h"

MeshStatistics::Stats MeshStatistics::gatherStatsSeq(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end)
{
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

		if (area < smallestArea && area > 0.0f) {
			smallestArea = area;
			stats.smallest = StatsTriangle{ triangle.a, triangle.b, triangle.c, area };
		}

		totalArea += area;

		begin++;
	}

	stats.avgArea = totalArea / count;

	return stats;
}

MeshStatistics::Stats MeshStatistics::gatherStats(std::vector<Triangle>::const_iterator begin, std::vector<Triangle>::const_iterator end)
{
	auto coreCount = std::thread::hardware_concurrency();
	auto triangleCount = std::distance(begin, end);
	auto trianglesPerCore = triangleCount / coreCount;

	std::vector<std::promise<MeshStatistics::Stats>> promises(coreCount);
	std::vector<std::thread> threads;
	std::vector<std::future<MeshStatistics::Stats>> futures;

	for (size_t idx = 0; idx < coreCount; idx++) {
		auto finish = begin + trianglesPerCore;

		if (finish > end) {
			finish = end;
		}

		threads.push_back(std::thread([&promises, idx, begin, finish] {
			promises[idx].set_value(MeshStatistics::gatherStatsSeq(begin, finish));
		}));
		futures.push_back(promises[idx].get_future());

		begin = finish;
	}

	std::vector<MeshStatistics::Stats> stats;

	for (auto& future : futures) {
		stats.push_back(future.get());
	}

	for (auto& thread : threads) {
		thread.join();
	}

	MeshStatistics::Stats combinedStats{ stats[0].smallest, stats[0].largest, 0.0f };
	float totalArea = 0.0f;

	for (auto& stat : stats) {
		if (stat.smallest.area < combinedStats.smallest.area) {
			combinedStats.smallest = stat.smallest;
		}

		if (stat.largest.area > combinedStats.largest.area) {
			combinedStats.largest = stat.largest;
		}

		totalArea += stat.avgArea;
	}

	combinedStats.avgArea = totalArea / stats.size();

	return combinedStats;
}
