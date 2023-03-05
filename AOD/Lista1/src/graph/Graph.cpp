#include "Graph.h"

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <ranges>

void Graph::operator=(const Graph& other) {
	is_directed_ = other.is_directed_;
	n_ = other.n_;
	m_ = other.m_;
	vertices_ = other.vertices_;
}

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

	for (auto& v : tree_) {
		std::cout << v.first << " -> ";

		for (int i = 0; i < v.second.size(); ++i) {
			if (i < v.second.size() - 1) {
				std::cout << v.second[i] << ", ";
			} else {
				std::cout << v.second[i] << "\n";
			}
		}
	}
}

void Graph::DFS(int v) {
	visited_[v] = true;
	std::cout << v << std::endl;
	
	for (auto& i : vertices_[v]) {
		if (!visited_[i]) {
			DFS(i);
			tree_[v].push_back(i);
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

	for (const auto& v : std::views::iota(1, n_ + 1)) {
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

void Graph::SCCs() {
	std::stack<int> stack;

	resetVisitedVertices();

	for (const auto& v : vertices_) {
		if (visited_[v.first] == false) {
			fillOrder(v.first, stack);
		}
	}

	Graph g = getTranspose(*this);

	resetVisitedVertices();

	while (!stack.empty()) {
		int v = stack.top();
		stack.pop();

		if (visited_[v] == false) {
			g.DFSUtil(v, visited_);
			std::cout << std::endl;
		}
	}

}

void Graph::fillOrder(const int v, std::stack<int>& stack) {
	visited_[v] = true;

	for (const auto& u : vertices_[v]) {
		if (!visited_[u]) {
			fillOrder(u, stack);
		}
	}

	stack.push(v);
}

void Graph::DFSUtil(int v, std::vector<bool>& visited) {
	visited[v] = true;
	std::cout << v << " ";

	for (const auto& u : vertices_[v]) {
		if (!visited[u]) {
			DFSUtil(u, visited);
		}
	}
}

bool Graph::isBipartite() {
	std::vector<int> color(n_ + 1, -1);

	std::queue<std::pair<int, int>> queue;

	std::vector<int> v1, v2;

	for (const auto& v : std::views::iota(1, n_ + 1)) {
		if (color[v] == -1) {
			queue.push({ v, 0 });
			color[v] = 0;
			v1.push_back(v);

			while (!queue.empty()) {
				std::pair<int, int> p = queue.front();
				queue.pop();

				int u = p.first;
				int w = p.second;

				for (int j : vertices_[u]) {
					if (color[j] == w) {
						return false;
					}

					if (color[j] == -1) {
						if (w) {
							color[j] = 0;
							v1.push_back(j);
						} else {
							color[j] = 1;
							v2.push_back(j);
						}

						queue.push({ j, color[j] });
					}
				}
			}
		}
	}

	if (n_ <= 200) {
		std::cout << "V1:\n";
		for (const auto& v : v1) {
			std::cout << v << " ";
		}

		std::cout << std::endl << std::endl;

		std::cout << "V2:\n";
		for (const auto& v : v2) {
			std::cout << v << " ";
		}

		std::cout << std::endl << std::endl;
	}

	return true;
}

Graph Graph::getTranspose(const Graph& other) {
	Graph g = *this;
	g.vertices_.clear();
	
	for (const auto& v : std::views::iota(1, g.n_ + 1)) {
		for (const auto& u : vertices_[v]) {
			g.vertices_[u].push_back(v);
		}
	}

	return g;
}