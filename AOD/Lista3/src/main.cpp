#include <iostream>

#include "Graph.h"
#include "dijkstra/Dijkstra.h"

int main() {

	aod::Graph g = aod::loadGraphFromFile("tests/aod.txt");
	auto dijkstra_test = aod::dijkstra(g, 1, 6);

	std::cout << "testing\n";
}