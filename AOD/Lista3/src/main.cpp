#include <chrono>
#include <iostream>
#include <execution>
#include <thread>

#include "DijkstraBenchmark.h"
#include "Graph.h"
#include "dijkstra/Dijkstra.h"

#define DEBUG 1

int main()
{
	auto dijkstra_benchmark = aod::DijkstraBenchmark(
		"benchmarks/inputs/USA-road-d/USA-road-d.NY.gr",
		"benchmarks/inputs/USA-road-d/USA-road-d.NY.ss",
		"benchmarks/inputs/USA-road-d/USA-road-d.NY.p2p");

	//auto dijkstra_benchmark = aod::DijkstraBenchmark(
	//	"benchmarks/inputs/Random4-n/Random4-n.14.0.gr",
	//	"benchmarks/inputs/Random4-n/Random4-n.14.0.ss",
	//	"benchmarks/inputs/Random4-n/Random4-n.14.0.p2p");

	/*auto dijkstra_benchmark = aod::DijkstraBenchmark(
		"tests/aod.txt",
		"tests/sources.txt",
		"tests/paths.txt");*/

	auto start = std::chrono::steady_clock::now();

	auto dijkstra_result = dijkstra_benchmark.normalDijkstraPathsBenchmark();

	auto end = std::chrono::steady_clock::now();
#if DEBUG 1
	std::cout << "(Dijkstra) time elapsed: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " milliseconds."
		<< std::endl;
#endif

	start = std::chrono::steady_clock::now();

	auto dial_dijkstra_result = dijkstra_benchmark.dialDijkstraPathsBenchmark();

	end = std::chrono::steady_clock::now();
#if DEBUG 1
	std::cout << "(Dijkstra Dial) time elapsed: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " milliseconds."
		<< std::endl;
#endif

	start = std::chrono::steady_clock::now();

	auto radix_dijkstra_result = dijkstra_benchmark.radixHeapDijkstraPathsBenchmark();

	end = std::chrono::steady_clock::now();
#if DEBUG 1
	std::cout << "(Dijkstra Radix Heap) time elapsed: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " milliseconds."
		<< std::endl;
#endif
}
