#pragma once

#include "Graph.h"

namespace aod {

	struct DijkstraBenchmarkSources {
		std::vector<int> sources;
	};

	DijkstraBenchmarkSources loadSourcesFromFile(const std::string& filename);

	struct DijkstraBenchmarkPathsGoals {
		std::vector<std::pair<int, int>> path_goals;
	};

	DijkstraBenchmarkPathsGoals loadPathGoalsFromFile(const std::string& filename);

	class DijkstraBenchmark {
	public:
		DijkstraBenchmark(aod::Graph& graph, DijkstraBenchmarkSources sources);

		void sourcesBenchmark();

	private:
		aod::Graph& graph;
		DijkstraBenchmarkSources& benchmark_sources;
	};
}