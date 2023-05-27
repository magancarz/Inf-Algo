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
		DijkstraBenchmark(
			const std::string& graph_filename,
			const std::string& sources_filename,
			const std::string& paths_filename);

		std::vector<std::vector<unsigned int>> normalDijkstraSourcesBenchmark();
		std::vector<std::vector<unsigned int>> dialDijkstraSourcesBenchmark();
		std::vector<std::vector<unsigned int>> radixHeapDijkstraSourcesBenchmark();

		std::vector<std::vector<unsigned int>> normalDijkstraPathsBenchmark();
		std::vector<std::vector<unsigned int>> dialDijkstraPathsBenchmark();
		std::vector<std::vector<unsigned int>> radixHeapDijkstraPathsBenchmark();

		std::vector<std::vector<unsigned int>> dijkstraSourcesBenchmark(std::vector<unsigned int> (*dijkstra_implementation)(Graph& graph, unsigned int src));
		std::vector<std::vector<unsigned int>> dijkstraPathsBenchmark(std::vector<unsigned int> (*dijkstra_implementation)(Graph& graph, unsigned int from, unsigned int to));

		Graph graph;
		DijkstraBenchmarkSources benchmark_sources;
		DijkstraBenchmarkPathsGoals benchmark_pairs;
	};
}