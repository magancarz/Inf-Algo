#include <chrono>
#include <iostream>
#include <execution>
#include <mutex>

#include "DijkstraBenchmark.h"
#include "Graph.h"
#include "dijkstra/Dijkstra.h"

#define DEBUG 0

int main() {

	//aod::Graph g = aod::loadGraphFromFile("benchmarks/inputs/USA-road-t/USA-road-t.CTR.gr");
	aod::Graph g = aod::loadGraphFromFile("benchmarks/inputs/USA-road-t/USA-road-t.NY.gr");
	aod::DijkstraBenchmarkSources sources = aod::loadSourcesFromFile("benchmarks/inputs/USA-road-d/USA-road-d.NY.ss");
	//aod::Graph g = aod::loadGraphFromFile("tests/aod.txt");

	std::cout << "Graph loaded\n";

	std::vector<std::vector<unsigned int>> distances;
	distances.reserve(sources.sources.size());
	//std::vector<std::vector<unsigned int>> path(2);
	
	std::mutex dijkstra_mutex;
	std::for_each(sources.sources.begin(), sources.sources.end(),
		[&](int source)
		{
			const auto start = std::chrono::steady_clock::now();

			//path[source] = aod::dijkstraDial(g, source, g.v);
			auto result = aod::dijkstraDialWithOnlyDistances(g, source);

			//std::lock_guard<std::mutex> guard(dijkstra_mutex);
			distances.push_back(result);

			const auto end = std::chrono::steady_clock::now();
#if DEBUG 1
			std::cout << "(Dijkstra sources benchmark) source: "
				+ std::to_string(source)
				+ ", time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds." << std::endl;
#endif
		});

	std::vector<std::vector<unsigned int>> distances2;
	distances2.reserve(sources.sources.size());
	//std::vector<std::vector<unsigned int>> sources2(2);

	std::for_each(sources.sources.begin(), sources.sources.end(),
		[&](int source)
		{
			const auto start = std::chrono::steady_clock::now();

			//sources2[source] = aod::dijkstra(g, source, g.v);
			auto result = aod::dijkstraWithOnlyDistances(g, source);

			//std::lock_guard<std::mutex> guard(dijkstra_mutex);
			distances2.push_back(result);

			const auto end = std::chrono::steady_clock::now();
#if DEBUG 1
			std::cout << "(Dijkstra sources benchmark) source: "
				+ std::to_string(source)
				+ ", time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds." << std::endl;
#endif
		});

	std::vector<std::vector<unsigned int>> distances3;
	distances3.reserve(sources.sources.size());
	//std::vector<std::vector<unsigned int>> sources3(2);

	std::for_each(sources.sources.begin(), sources.sources.end(),
		[&](int source)
		{
			const auto start = std::chrono::steady_clock::now();

			//sources3[source] = aod::dijkstraRadix(g, source, g.v);
			auto result = aod::dijkstraRadixWithOnlyDistances(g, source);

			//std::lock_guard<std::mutex> guard(dijkstra_mutex);
			distances3.push_back(result);

			const auto end = std::chrono::steady_clock::now();
#if DEBUG 1
			std::cout << "(Dijkstra sources benchmark) source: "
				+ std::to_string(source)
				+ ", time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds." << std::endl;
#endif
		});

	if (distances == distances2 && distances == distances3) {
		std::cout << "Essa\n";
	}

	/*if (path[1] == sources2[1] && path[1] == sources3[1]) {
		std::cout << "Essa\n";
	}*/

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
