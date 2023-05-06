#include <chrono>
#include <iostream>

#include "DijkstraBenchmark.h"
#include "Graph.h"
#include "dijkstra/Dijkstra.h"


int main() {

	//aod::Graph g = aod::loadGraphFromFile("benchmarks/inputs/USA-road-t/USA-road-t.CTR.gr");
	aod::Graph g = aod::loadGraphFromFile("benchmarks/inputs/USA-road-t/USA-road-t.NY.gr");
	//aod::Graph g = aod::loadGraphFromFile("tests/aod.txt");

	std::cout << "Graph loaded\n";

	auto start = std::chrono::steady_clock::now();
	auto test1 = aod::dijkstra(g, 1, g.v);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;

	start = std::chrono::steady_clock::now();
	auto test2 = aod::dijkstraDial(g, 1, g.v);
	end = std::chrono::steady_clock::now();
	std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;

	start = std::chrono::steady_clock::now();
	auto test3 = aod::dijkstraRadix(g, 1, g.v);
	end = std::chrono::steady_clock::now();

	std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;
}
