#include "src/graph/Graph.h"

#include <iostream>
#include <chrono>

void runTests() {
    for (const auto& i : { 1, 2, 3, 4, 5, 6 }) {
        auto g = new Graph();
        std::string filepath = "../tests/2/g2a-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        auto start = std::chrono::steady_clock::now();
        std::cout << "Running topological sort on " << filepath << std::endl;
        g->topologicalSort();
        auto end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
        delete g;

        std::cout << "----------\n";

        g = new Graph();
        filepath = "../tests/2/g2b-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        start = std::chrono::steady_clock::now();
        std::cout << "Running topological sort on " << filepath << std::endl;
        g->topologicalSort();
        end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
        delete g;

        std::cout << "----------\n";
    }

    for (const auto& i : { 1, 2, 3, 4, 5, 6 }) {
        auto g = new Graph();
        std::string filepath = "../tests/3/g3-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        auto start = std::chrono::steady_clock::now();
        std::cout << "Running SCCs algorithm on " << filepath << std::endl;
        g->SCCs();
        auto end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
        delete g;

        std::cout << "----------\n";
    }

	for (const auto& i : { 1, 2, 3, 4, 5, 6 }) {
        auto g = new Graph();
		std::string filepath = "../tests/4/d4a-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        auto start = std::chrono::steady_clock::now();
		std::cout << "Running isBipartite() on " << filepath << std::endl;
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        auto end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
        delete g;

        std::cout << "----------\n";

        g = new Graph();
		filepath = "../tests/4/d4b-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
		std::cout << "Running isBipartite() on " << filepath << std::endl;
        start = std::chrono::steady_clock::now();
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
        delete g;

        std::cout << "----------\n";

        g = new Graph();
        filepath = "../tests/4/u4a-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        std::cout << "Running isBipartite() on " << filepath << std::endl;
        start = std::chrono::steady_clock::now();
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
        delete g;

        std::cout << "----------\n";

        g = new Graph();
        filepath = "../tests/4/u4b-" + std::to_string(i) + ".txt";
        g->loadDataFromFileToGraph(filepath);
        std::cout << "Running isBipartite() on " << filepath << std::endl;
        start = std::chrono::steady_clock::now();
        g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
        end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
        delete g;

        std::cout << "----------\n";
	}
}

int main() {
	runTests();
//    auto g = new Graph();
//    std::string filepath = "../tests/l0_4.txt";
//    g->loadDataFromFileToGraph(filepath);
//    auto start = std::chrono::steady_clock::now();
//    std::cout << "Running topological sort on " << filepath << std::endl;
//    g->topologicalSort();
//    auto end = std::chrono::steady_clock::now();
//    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;
//    g->isBipartite() ? std::cout << "Yes\n" : std::cout << "No\n";
//    delete g;
}