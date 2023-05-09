#pragma once

#include <queue>

#include "BenchmarkPlayer.h"

class MinimaxBenchmark {
public:
	void benchmark();
	void battleBenchmark();
	BenchmarkPlayer testPlayerWithEveryConfiguration(BenchmarkPlayer& player);
	int runConfiguration(BenchmarkPlayer& player1, BenchmarkPlayer& player2);

private:
	void saveResultsToFile(std::vector<BenchmarkResult>& benchmark_results);
};