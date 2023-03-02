#include "Graph.h"

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <ranges>

void Graph::loadDataFromFileToGraph(const std::string& path) {

	std::ifstream file_stream(path);
	if (file_stream.is_open()) {
		std::string line;
		getline(file_stream, line);
		if (line[0] == 'D') {
			is_directed_ = true;
		}

		getline(file_stream, line);
		n_ = std::stoi(line);

		getline(file_stream, line);
		m_ = std::stoi(line);

		while (getline(file_stream, line)) {
			std::istringstream iss(line);
			std::string u, v;
			iss >> u;
			iss >> v;

			vertices_[std::stoi(u)].push_back(std::stoi(v));
		}

		file_stream.close();
	} else {
		std::cout << "Unable to open file!\n_";
	}
}

void Graph::DFS() {
	resetVisitedVertices();

	DFS(1);
}

void Graph::DFS(int v) {
	visited_[v] = true;
	std::cout << v << std::endl;
	
	for (auto& i : vertices_[v]) {
		if (!visited_[i]) {
			DFS(i);
		}
	}
}

void Graph::BFS() {
	resetVisitedVertices();

	std::list<int> queue;

	visited_[1] = true;
	queue.push_back(1);

	int s;
	while (!queue.empty()) {
		s = queue.front();
		std::cout << s << std::endl;
		queue.pop_front();

		for (const auto& adjacent : vertices_[s]) {
			if(!visited_[adjacent]) {
				visited_[adjacent] = true;
				queue.push_back(adjacent);
			}
		}
	}
}

void Graph::topologicalSort() {
	std::stack<int> stack;

	resetVisitedVertices();

	for (const auto& v : std::views::iota(1, n_)) {
		if (visited_[v] == false) {
			topologicalSortUtil(v, stack);
		}
	}

	while (!stack.empty()) {
		std::cout << stack.top() << std::endl;
		stack.pop();
	}
}

void Graph::topologicalSortUtil(int v, std::stack<int>& stack) {
	visited_[v] = true;

	for (const auto& i : vertices_[v]) {
		if (!visited_[i]) {
			topologicalSortUtil(i, stack);
		}
	}

	stack.push(v);
}