#include <chrono>
#include <iostream>
#include <execution>

#include "DijkstraBenchmark.h"
#include "Graph.h"
#include "dijkstra/Dijkstra.h"

#define DEBUG 1

int main() {

	//aod::Graph g = aod::loadGraphFromFile("benchmarks/inputs/USA-road-t/USA-road-t.CTR.gr");
	aod::Graph g = aod::loadGraphFromFile("benchmarks/inputs/USA-road-t/USA-road-t.NY.gr");
	//aod::Graph g = aod::loadGraphFromFile("tests/aod.txt");

	std::cout << "Graph loaded\n";

	std::vector<unsigned int> sources = { 1 };
	/*for (int i = 1; i <= g.v; ++i) {
		sources[i - 1] = i;
	}*/

	std::vector<std::vector<unsigned int>> distances(2);
	
	std::for_each(std::execution::par, sources.begin(), sources.end(),
		[&](int source)
		{
			const auto start = std::chrono::steady_clock::now();

			distances[source] = aod::dijkstraDialWithOnlyDistances(g, source);

			const auto end = std::chrono::steady_clock::now();
			std::cout << "(Dijkstra sources benchmark) source: "
				+ std::to_string(source)
				+ ", time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds." << std::endl;
		});

	std::vector<std::vector<unsigned int>> distances2(2);

	std::for_each(std::execution::par, sources.begin(), sources.end(),
		[&](int source)
		{
			const auto start = std::chrono::steady_clock::now();

			distances2[source] = aod::dijkstraWithOnlyDistances(g, source);

			const auto end = std::chrono::steady_clock::now();
			std::cout << "(Dijkstra sources benchmark) source: "
				+ std::to_string(source)
				+ ", time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds." << std::endl;
		});

	std::vector<std::vector<unsigned int>> distances3(2);

	std::for_each(std::execution::par, sources.begin(), sources.end(),
		[&](int source)
		{
			const auto start = std::chrono::steady_clock::now();

			distances3[source] = aod::dijkstraRadixWithOnlyDistances(g, source);

			const auto end = std::chrono::steady_clock::now();
			std::cout << "(Dijkstra sources benchmark) source: "
				+ std::to_string(source)
				+ ", time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds." << std::endl;
		});

	if (distances[1] == distances2[1] && distances[1] == distances3[1]) {
		std::cout << "Essa\n";
	}

	auto start = std::chrono::steady_clock::now();/*
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

	std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;*/
}
