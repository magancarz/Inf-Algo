#pragma once

#include <string>
#include <vector>
#include <map>
#include <stack>

class Graph {
public:
	Graph() = default;
	virtual ~Graph() = default;

	void loadDataFromFileToGraph(const std::string& path);

	void DFS();
	void BFS();

	void topologicalSort();

private:
	void resetVisitedVertices() { visited_ = std::vector<bool>(n_ + 1, false); }

	void DFS(int v);

	void topologicalSortUtil(int v, std::stack<int>& stack);

	bool is_directed_ = false;
	int n_ = 0;
	int m_ = 0;
	std::map<int, std::vector<int>> vertices_;

	std::vector<bool> visited_;
};
