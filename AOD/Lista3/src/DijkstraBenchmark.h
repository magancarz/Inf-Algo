#pragma once

#include "Graph.h"

#define NO_OF_THREADS 1

namespace aod {

	struct DijkstraBenchmarkSources {
		std::vector<int> sources;
	};

	DijkstraBenchmarkSources loadSourcesFromFile(const std::string& filename);

	struct DijkstraBenchmarkPathsGoals {
		std::vector<std::pair<int, int>> path_goals;
	};

	DijkstraBenchmarkPathsGoals loadPathGoalsFromFile(const std::string& filename);

	struct PathResult
	{
		unsigned int from;
		unsigned int to;
		unsigned int length;
	};

	class DijkstraBenchmark {
	public:
		DijkstraBenchmark() = default;

		DijkstraBenchmark(
			const std::string& graph_filename,
			const std::string& sources_filename,
			const std::string& paths_filename);

		std::vector<std::vector<unsigned int>> normalDijkstraSourcesBenchmark();
		std::vector<std::vector<unsigned int>> dialDijkstraSourcesBenchmark();
		std::vector<std::vector<unsigned int>> radixHeapDijkstraSourcesBenchmark();

		std::vector<PathResult> normalDijkstraPathsBenchmark();
		std::vector<PathResult> dialDijkstraPathsBenchmark();
		std::vector<PathResult> radixHeapDijkstraPathsBenchmark();

		std::vector<std::vector<unsigned int>> dijkstraSourcesBenchmark(std::vector<unsigned int> (*dijkstra_implementation)(Graph& graph, unsigned int src));
		std::vector<PathResult> dijkstraPathsBenchmark(unsigned int (*dijkstra_implementation)(Graph& graph, unsigned int from, unsigned int to));

		void saveSourcesBenchmarkResults(const std::string& filename, const std::string& algo_type, const std::vector<unsigned int>&dijkstra_result, const std::vector<unsigned int>& dial_dijkstra_result, const std::vector<unsigned int>& radix_dijkstra_result);
		void savePathsBenchmarkResults(const std::string& filename, const std::string& algo_type, const std::vector<unsigned int>& dijkstra_result, const std::vector<unsigned int>& dial_dijkstra_result, const std::vector<unsigned int>& radix_dijkstra_result);

		Graph graph;
		DijkstraBenchmarkSources benchmark_sources;
		DijkstraBenchmarkPathsGoals benchmark_pairs;
	};
}