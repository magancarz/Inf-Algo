#include "graph/Graph.h"

#include <iostream>

int main() {
	Graph g;
	g.loadDataFromFileToGraph("tests/2/g2a-1.txt");

	std::cout << "Topological sort:\n";
	g.topologicalSort();
}
