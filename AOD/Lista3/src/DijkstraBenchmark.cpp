#include "DijkstraBenchmark.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <execution>
#include <sstream>

#include "dijkstraImpl/Dijkstra.h"

namespace aod {

	DijkstraBenchmarkSources loadSourcesFromFile(const std::string& filename)
	{
		if (filename.empty()) return {};

		std::ifstream file_stream(filename);
		if (file_stream.is_open()) {

			DijkstraBenchmarkSources benchmark_sources{};

			std::string line;
			while (getline(file_stream, line)) {

				if (line[0] == 'p') {

					std::stringstream iss(line);
					std::string p, aux, sp, ss, no_of_sources;
					iss >> p;
					iss >> aux;
					iss >> sp;
					iss >> ss;
					iss >> no_of_sources;
				}

				if (line[0] == 's') {
					std::stringstream iss(line);
					std::string s, source;
					iss >> s;
					iss >> source;
					benchmark_sources.sources.push_back(std::stoi(source));
				}

				if (line[0] == 'c') {
					//ignore
				}
			}

			file_stream.close();

			return benchmark_sources;
		}

		throw std::runtime_error("Error: unable to open sources file!");
	}

	DijkstraBenchmarkPathsGoals loadPathGoalsFromFile(const std::string& filename)
	{
		if (filename.empty()) return {};

		std::ifstream file_stream(filename);
		if (file_stream.is_open()) {

			DijkstraBenchmarkPathsGoals benchmark_paths_goals{};

			std::string line;
			while (getline(file_stream, line)) {

				if (line[0] == 'p') {

					std::stringstream iss(line);
					std::string p, aux, sp, p2p, no_of_path_goals;
					iss >> p;
					iss >> aux;
					iss >> sp;
					iss >> p2p;
					iss >> no_of_path_goals;
				}

				if (line[0] == 'q') {
					std::stringstream iss(line);
					std::string p, from, to;
					iss >> p;
					iss >> from;
					iss >> to;
					benchmark_paths_goals.path_goals.push_back({ std::stoi(from), std::stoi(to) });
				}

				if (line[0] == 'c') {
					//ignore
				}
			}

			file_stream.close();

			return benchmark_paths_goals;
		}

		throw std::runtime_error("Error: unable to open paths goals file!");
	}

	DijkstraBenchmark::DijkstraBenchmark(const std::string& graph_filename, const std::string& sources_filename, const std::string& paths_filename)
	{
		graph = loadGraphFromFile(graph_filename);
		benchmark_sources = loadSourcesFromFile(sources_filename);
		benchmark_pairs = loadPathGoalsFromFile(paths_filename);
	}

	std::vector<std::vector<uint64_t>> DijkstraBenchmark::normalDijkstraSourcesBenchmark()
	{
		return dijkstraSourcesBenchmark(&aod::dijkstraWithOnlyDistances);
	}

	std::vector<std::vector<uint64_t>> DijkstraBenchmark::dialDijkstraSourcesBenchmark()
	{
		return dijkstraSourcesBenchmark(&aod::dijkstraDialWithOnlyDistances);
	}

	std::vector<std::vector<uint64_t>> DijkstraBenchmark::radixHeapDijkstraSourcesBenchmark()
	{
		return dijkstraSourcesBenchmark(&aod::dijkstraRadixWithOnlyDistances);
	}

	std::vector<PathResult> DijkstraBenchmark::normalDijkstraPathsBenchmark()
	{
		return dijkstraPathsBenchmark(&aod::dijkstra);
	}

	std::vector<PathResult> DijkstraBenchmark::dialDijkstraPathsBenchmark()
	{
		return dijkstraPathsBenchmark(&aod::dijkstraDial);
	}

	std::vector<PathResult> DijkstraBenchmark::radixHeapDijkstraPathsBenchmark()
	{
		return dijkstraPathsBenchmark(&aod::dijkstraRadix);
	}

	std::vector<std::vector<uint64_t>> DijkstraBenchmark::dijkstraSourcesBenchmark(std::vector<uint64_t>(*dijkstra_implementation)(Graph& graph, unsigned int src))
	{
		std::vector<std::vector<uint64_t>> distances;
		distances.reserve(benchmark_sources.sources.size());

		std::mutex mtx;
		std::for_each(std::execution::par, benchmark_sources.sources.begin(), benchmark_sources.sources.end(),
		[&](int source)
		{
			const auto start = std::chrono::steady_clock::now();

			const auto result = dijkstra_implementation(graph, source);

			{
				std::lock_guard<std::mutex> lock(mtx);
				distances.push_back(result);
			}

			const auto end = std::chrono::steady_clock::now();
		});

		return distances;
	}

	std::vector<PathResult> DijkstraBenchmark::dijkstraPathsBenchmark(uint64_t(*dijkstra_implementation)(Graph& graph, unsigned int from, unsigned int to))
	{
		std::vector<PathResult> paths;
		paths.reserve(benchmark_pairs.path_goals.size());

		std::vector<int> blocks_iter(NO_OF_THREADS);
		const int block_size = benchmark_pairs.path_goals.size() / NO_OF_THREADS;
		for (int i = 0; i < blocks_iter.size(); ++i)
		{
			blocks_iter[i] = i;
		}

		/*std::mutex mtx;
		std::for_each(std::execution::par, blocks_iter.begin(), blocks_iter.end(),
		[&](int it)
		{
			for (int i = it * block_size; i < std::min((it + 1) * block_size, static_cast<int>(benchmark_pairs.path_goals.size())); ++i)
			{
				
			}
		});*/

		const auto start = std::chrono::steady_clock::now();

		unsigned int from = benchmark_pairs.path_goals[0].first;
		unsigned int to = benchmark_pairs.path_goals[0].second;
		const auto result = dijkstra_implementation(graph, from, to);

		{
			paths.push_back({ from, to, result });
		}

		const auto end = std::chrono::steady_clock::now();

		return paths;
	}
}