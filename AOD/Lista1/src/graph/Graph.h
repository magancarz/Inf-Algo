#pragma once

#include <string>
#include <vector>
#include <map>
#include <stack>

class Graph {
public:
	Graph() = default;
	virtual ~Graph() = default;

	void operator=(const Graph& other);

	void loadDataFromFileToGraph(const std::string& path);

	void DFS(bool print_tree = false);
	void BFS(bool print_tree = false);

	void topologicalSort();

	void SCCs();

	bool isBipartite();

	Graph getTranspose(const Graph& other);

private:
	void resetVisitedVertices() { visited = std::vector<bool>(n + 1, false); }

	void DFS(int v);

	void printTree();

	void topologicalSortUtil(int v, std::stack<int>& stack);

	void fillOrder(int v, std::stack<int>& stack);
	void DFSUtil(int v, std::vector<bool>& visited);

	bool is_directed = false;
	int n = 0;
	int m = 0;
	std::map<int, std::vector<int>> vertices;

	std::vector<bool> visited;
	std::map<int, std::vector<int>> tree;

    int scc_amt = 0;
    int scc_size = 0;
};