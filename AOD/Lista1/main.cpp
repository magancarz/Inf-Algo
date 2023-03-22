#include "src/graph/Graph.h"

#include <iostream>

void runTests() {
    for (const auto& i : { 1, 2, 3, 4, 5, 6 }) {
        auto g = new Graph();
        std::string filepath = "../tests/2/g2a-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        std::cout << "Running topological sort on " << filepath << std::endl;
        g->topologicalSort();
        delete g;

        g = new Graph();
        filepath = "../tests/2/g2b-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        std::cout << "Running topological sort on " << filepath << std::endl;
        g->topologicalSort();
        delete g;
    }

    for (const auto& i : { 1, 2, 3, 4, 5, 6 }) {
        auto g = new Graph();
        std::string filepath = "../tests/3/g3-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        std::cout << "Running SCCs algorithm on " << filepath << std::endl;
        g->SCCs();
        delete g;
    }

	for (const auto& i : { 1, 2, 3, 4, 5, 6 }) {
        auto g = new Graph();
		std::string filepath = "../tests/4/d4a-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
		std::cout << "Running isBipartite() on " << filepath << std::endl;
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        delete g;

        g = new Graph();
		filepath = "../tests/4/d4b-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
		std::cout << "Running isBipartite() on " << filepath << std::endl;
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        delete g;

        g = new Graph();
        filepath = "../tests/4/u4a-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        std::cout << "Running isBipartite() on " << filepath << std::endl;
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        delete g;

        g = new Graph();
        filepath = "../tests/4/u4b-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        std::cout << "Running isBipartite() on " << filepath << std::endl;
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        delete g;
	}
}

int main() {
	//runTests();
    auto g = new Graph();
    std::string filepath = "../tests/4/d4b-5.txt";
    g->loadDataFromFileToGraph(filepath);
    std::cout << "Running topological sort on " << filepath << std::endl;
    g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
    delete g;
}