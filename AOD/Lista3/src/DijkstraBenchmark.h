#pragma once

#include "Graph.h"

#define NO_OF_THREADS 2

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
		uint64_t from;
		uint64_t to;
		uint64_t length;
	};

	class DijkstraBenchmark {
	public:
		DijkstraBenchmark() = default;

		DijkstraBenchmark(
			const std::string& graph_filename,
			const std::string& sources_filename,
			const std::string& paths_filename);

		std::vector<std::vector<uint64_t>> normalDijkstraSourcesBenchmark();
		std::vector<std::vector<uint64_t>> dialDijkstraSourcesBenchmark();
		std::vector<std::vector<uint64_t>> radixHeapDijkstraSourcesBenchmark();

		std::vector<PathResult> normalDijkstraPathsBenchmark();
		std::vector<PathResult> dialDijkstraPathsBenchmark();
		std::vector<PathResult> radixHeapDijkstraPathsBenchmark();

		std::vector<std::vector<uint64_t>> dijkstraSourcesBenchmark(std::vector<uint64_t> (*dijkstra_implementation)(Graph& graph, unsigned int src));
		std::vector<PathResult> dijkstraPathsBenchmark(uint64_t (*dijkstra_implementation)(Graph& graph, unsigned int from, unsigned int to));

		void saveSourcesBenchmarkResults(const std::string& filename, const std::string& algo_type, const std::vector<uint64_t>&dijkstra_result, const std::vector<unsigned int>& dial_dijkstra_result, const std::vector<unsigned int>& radix_dijkstra_result);
		void savePathsBenchmarkResults(const std::string& filename, const std::string& algo_type, const std::vector<uint64_t>& dijkstra_result, const std::vector<unsigned int>& dial_dijkstra_result, const std::vector<unsigned int>& radix_dijkstra_result);

		Graph graph;
		DijkstraBenchmarkSources benchmark_sources;
		DijkstraBenchmarkPathsGoals benchmark_pairs;
	};
}