#include "graph/Graph.h"

#include <iostream>

int main() {
	Graph g;
	g.loadDataFromFileToGraph("tests/scc_test.txt");
	
	g.SCCs();
}