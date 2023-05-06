#pragma once

#include "BenchmarkPlayer.h"

class MinimaxBenchmark {
public:
	void benchmark();

	int runConfiguration(BenchmarkPlayer& player1, BenchmarkPlayer& player2);
};