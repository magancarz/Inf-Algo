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
		"benchmarks/inputs/USA-road-d/USA-road-d.NY.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.BAY.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.COL.gr",
		/*"benchmarks/inputs/USA-road-d/USA-road-d.FLA.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.NW.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.NE.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.CAL.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.LKS.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.E.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.W.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.CTR.gr"*/
	};

	std::vector<std::string> sources_inputs =
	{
		"benchmarks/inputs/USA-road-d/USA-road-d.NY.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.BAY.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.COL.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.FLA.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.NW.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.NE.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.CAL.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.LKS.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.E.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.W.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.CTR.ss"
	};

	std::vector<std::string> paths_inputs =
	{
		"benchmarks/inputs/USA-road-d/USA-road-d.NY.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.BAY.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.COL.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.FLA.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.NW.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.NE.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.CAL.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.LKS.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.E.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.W.p2p",
		"benchmarks/inputs/USA-road-d/USA-road-d.CTR.p2p"
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

		auto dijkstra_result = dijkstra_benchmark.normalDijkstraSourcesBenchmark();

		auto end = std::chrono::steady_clock::now();
	#if DEBUG 1
		std::cout << "(Dijkstra) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif
		dijkstra_results.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

		start = std::chrono::steady_clock::now();

		auto dial_dijkstra_result = dijkstra_benchmark.dialDijkstraSourcesBenchmark();

		end = std::chrono::steady_clock::now();
	#if DEBUG 1
		std::cout << "(Dijkstra Dial) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif
		dial_results.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

		start = std::chrono::steady_clock::now();

		auto radix_dijkstra_result = dijkstra_benchmark.radixHeapDijkstraSourcesBenchmark();

		end = std::chrono::steady_clock::now();
	#if DEBUG 1
		std::cout << "(Dijkstra Radix Heap) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif
		radix_results.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	}

	std::ofstream results_file("sources_benchmark_results.txt");
	if (results_file.is_open())
	{
		results_file << "Dijkstra sources results: (from graphs increasing in size)\n";
		for (auto& result : dijkstra_results)
		{
			results_file << result << std::endl;
		}
		results_file << std::endl;

		results_file << "Dial sources results: (from graphs increasing in size)\n";
		for (auto& result : dial_results)
		{
			results_file << result << std::endl;
		}
		results_file << std::endl;

		results_file << "Radix Heap sources results: (from graphs increasing in size)\n";
		for (auto& result : radix_results)
		{
			results_file << result << std::endl;
		}
	}
}