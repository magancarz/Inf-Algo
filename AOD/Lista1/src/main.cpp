#include "graph/Graph.h"

#include <iostream>

int main() {
	Graph g;
	g.loadDataFromFileToGraph("tests/bip_test.txt");
	
	g.isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
}