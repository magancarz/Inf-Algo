#pragma once

#include <string>
#include <vector>

class Graph {
public:
	Graph() = default;
	virtual ~Graph() = default;

	void loadDataFromFileToGraph(const std::string& path);

private:
	bool is_directed = false;
	int n = 0;
	int m = 0;
	std::vector<std::pair<int, int>> edges;
};
