#include "src/graph/Graph.h"

#include <iostream>

void runTests() {
	for (const auto& i : { 1, 2, 3, 4, 5, 6 }) {
		Graph g;
		std::string filepath = "../tests/2/g2a-" + std::to_string(i) + ".txt";
		g.loadDataFromFileToGraph(filepath);
		std::cout << "Running topological sort on " << filepath << std::endl;
		g.topologicalSort();

		filepath = "../tests/2/g2b-" + std::to_string(i) + ".txt";
		g.loadDataFromFileToGraph(filepath);
		std::cout << "Running topological sort on " << filepath << std::endl;
		g.topologicalSort();
	}
}

int main() {
	//runTests();
    Graph g;
    g.loadDataFromFileToGraph("../tests/4/d4b-6.txt");
    g.isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
}