#pragma once

#include "Graph.h"

#define NO_OF_THREADS 4

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

		std::vector<unsigned int> normalDijkstraPathsBenchmark();
		std::vector<unsigned int> dialDijkstraPathsBenchmark();
		std::vector<unsigned int> radixHeapDijkstraPathsBenchmark();

		std::vector<std::vector<unsigned int>> dijkstraSourcesBenchmark(std::vector<unsigned int> (*dijkstra_implementation)(Graph& graph, unsigned int src));
		std::vector<unsigned int> dijkstraPathsBenchmark(unsigned int (*dijkstra_implementation)(Graph& graph, unsigned int from, unsigned int to));

		Graph graph;
		DijkstraBenchmarkSources benchmark_sources;
		DijkstraBenchmarkPathsGoals benchmark_pairs;
	};
}