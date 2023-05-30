#include <chrono>
#include <iostream>
#include <execution>
#include <thread>
#include <fstream>

#include "DijkstraBenchmark.h"
#include "Graph.h"
#include "dijkstraImpl/Dijkstra.h"

#define DEBUG

int main(int argc, char* argv[])
{
	if (std::string(argv[3]) == "-ss")
	{
		aod::DijkstraBenchmark dijkstra_benchmark = aod::DijkstraBenchmark(
			argv[2],
			argv[4],
			"");

		auto start = std::chrono::steady_clock::now();

		auto dijkstra_result = dijkstra_benchmark.radixHeapDijkstraSourcesBenchmark();

		auto end = std::chrono::steady_clock::now();
	#ifdef DEBUG
		std::cout << "(Radix heap) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif
	
		std::ofstream file_stream(argv[6]);
		if (file_stream.is_open()) {
			file_stream << "p res sp ss dijkstra\n";
			file_stream << "f " << argv[2] << " " << argv[4] << std::endl;
			file_stream << "g " << dijkstra_benchmark.graph.v << " " << dijkstra_benchmark.graph.m << " " << findMinWeightInGraph(dijkstra_benchmark.graph) << " " << findMaxWeightInGraph(dijkstra_benchmark.graph) << std::endl;
			file_stream << "t " << static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / dijkstra_benchmark.benchmark_sources.sources.size() << std::endl;

			file_stream.close();
		}
	}
	else if (std::string(argv[3]) == "-p2p")
	{
		aod::DijkstraBenchmark dijkstra_benchmark = aod::DijkstraBenchmark(
			argv[2],
			"",
			argv[4]);

		auto start = std::chrono::steady_clock::now();

		auto dijkstra_result = dijkstra_benchmark.radixHeapDijkstraPathsBenchmark();

		auto end = std::chrono::steady_clock::now();
	#ifdef DEBUG
		std::cout << "(Radix heap) time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " milliseconds."
			<< std::endl;
	#endif

		std::ofstream file_stream(argv[6]);
		if (file_stream.is_open()) {
			file_stream << "f " << argv[2] << " " << argv[4] << std::endl;
			file_stream << "g " << dijkstra_benchmark.graph.v << " " << dijkstra_benchmark.graph.m << " " << findMinWeightInGraph(dijkstra_benchmark.graph) << " " << findMaxWeightInGraph(dijkstra_benchmark.graph) << std::endl;

			for (auto& path : dijkstra_result)
			{
				file_stream << "d " << path.from << " " << path.to << " " << path.length << std::endl;
			}

			file_stream.close();
		}
	}
}
