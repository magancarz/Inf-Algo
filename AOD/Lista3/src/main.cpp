#include <chrono>
#include <iostream>
#include <execution>
#include <fstream>

#include "DijkstraBenchmark.h"
#include "Graph.h"
#include "dijkstraImpl/Dijkstra.h"

#define DEBUG 1

int main()
{
	std::vector<std::string> graph_inputs =
	{
		"benchmarks/inputs/Square-n/Square-n.14.0.gr",
		"benchmarks/inputs/Square-n/Square-n.15.0.gr",
		"benchmarks/inputs/Square-n/Square-n.16.0.gr",
		"benchmarks/inputs/Square-n/Square-n.17.0.gr",
		"benchmarks/inputs/Square-n/Square-n.18.0.gr",
		"benchmarks/inputs/Square-n/Square-n.19.0.gr",
		"benchmarks/inputs/Square-n/Square-n.20.0.gr",
		"benchmarks/inputs/Square-n/Square-n.21.0.gr"
	};

	std::vector<std::string> sources_inputs =
	{
		"benchmarks/inputs/Square-n/Square-n.14.0.ss",
		"benchmarks/inputs/Square-n/Square-n.15.0.ss",
		"benchmarks/inputs/Square-n/Square-n.16.0.ss",
		"benchmarks/inputs/Square-n/Square-n.17.0.ss",
		"benchmarks/inputs/Square-n/Square-n.18.0.ss",
		"benchmarks/inputs/Square-n/Square-n.19.0.ss",
		"benchmarks/inputs/Square-n/Square-n.20.0.ss",
		"benchmarks/inputs/Square-n/Square-n.21.0.ss"
	};

	std::vector<std::string> paths_inputs =
	{
		"benchmarks/inputs/Square-n/Square-n.14.0.p2p",
		"benchmarks/inputs/Square-n/Square-n.15.0.p2p",
		"benchmarks/inputs/Square-n/Square-n.16.0.p2p",
		"benchmarks/inputs/Square-n/Square-n.17.0.p2p",
		"benchmarks/inputs/Square-n/Square-n.18.0.p2p",
		"benchmarks/inputs/Square-n/Square-n.19.0.p2p",
		"benchmarks/inputs/Square-n/Square-n.20.0.p2p",
		"benchmarks/inputs/Square-n/Square-n.21.0.p2p"
	};

	std::vector<unsigned int> dijkstra_results;
	std::vector<unsigned int> dial_results;
	std::vector<unsigned int> radix_results;
	for (int i = 0; i < graph_inputs.size(); ++i)
	{
		std::cout << "Running on " << graph_inputs[i] << std::endl;
		auto dijkstra_benchmark = aod::DijkstraBenchmark(
			graph_inputs[i],
			sources_inputs[i],
			paths_inputs[i]);

		auto start = std::chrono::steady_clock::now();

		auto dijkstra_result = dijkstra_benchmark.normalDijkstraPathsBenchmark();

		auto end = std::chrono::steady_clock::now();
	#if DEBUG 1
		std::cout << "(Dijkstra) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif
		dijkstra_results.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

		start = std::chrono::steady_clock::now();

		auto dial_dijkstra_result = dijkstra_benchmark.dialDijkstraPathsBenchmark();

		end = std::chrono::steady_clock::now();
	#if DEBUG 1
		std::cout << "(Dijkstra Dial) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif
		dial_results.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

		start = std::chrono::steady_clock::now();

		auto radix_dijkstra_result = dijkstra_benchmark.radixHeapDijkstraPathsBenchmark();

		end = std::chrono::steady_clock::now();
	#if DEBUG 1
		std::cout << "(Dijkstra Radix Heap) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif
		radix_results.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	}

	std::ofstream results_file("square_n_paths_benchmark_results.txt");
	if (results_file.is_open())
	{
		results_file << "Dijkstra paths results: (from graphs increasing in size)\n";
		for (auto& result : dijkstra_results)
		{
			results_file << result << std::endl;
		}
		results_file << std::endl;

		results_file << "Dial paths results: (from graphs increasing in size)\n";
		for (auto& result : dial_results)
		{
			results_file << result << std::endl;
		}
		results_file << std::endl;

		results_file << "Radix Heap paths results: (from graphs increasing in size)\n";
		for (auto& result : radix_results)
		{
			results_file << result << std::endl;
		}
	}
}