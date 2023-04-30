#include <iostream>

#include "Graph.h"
#include "dijkstra/Dijkstra.h"

int main() {

	aod::Graph g = aod::loadGraphFromFile("tests/aod.txt");
	auto test = aod::dijkstraDialWithOnlyDistances(g, 1, 20);

	std::cout << "testing\n";
}