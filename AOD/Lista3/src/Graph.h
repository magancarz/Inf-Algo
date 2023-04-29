#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace aod {

	struct Graph {
		int v = 0;
		int	m = 0;
		std::unordered_map<int, std::vector<std::pair<int, int>>> adjacency_list;
	};

	Graph loadGraphFromFile(const std::string& filename);
}
