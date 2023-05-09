#pragma once

#include <queue>

#include "BenchmarkPlayer.h"

class MinimaxBenchmark {
public:
	void benchmark();
	void battleBenchmark();
	BenchmarkPlayer testPlayerWithEveryConfiguration(BenchmarkPlayer& player);
	void geneticBenchmark();
	std::vector<BenchmarkPlayer> iterateGenetic(std::vector<BenchmarkPlayer>& players);
	BenchmarkResult testPlayerWithEveryPlayerInGroup(BenchmarkPlayer& player, std::vector<BenchmarkPlayer>& players);
	BenchmarkPlayer mixTwoPlayersStatistics(BenchmarkResult& player1, BenchmarkResult& player2);
	int runConfiguration(BenchmarkPlayer& player1, BenchmarkPlayer& player2);

private:
	void saveResultsToFile(std::vector<BenchmarkResult>& benchmark_results);
	void saveResultsToFile(std::vector<BenchmarkPlayer>& benchmark_results);
};