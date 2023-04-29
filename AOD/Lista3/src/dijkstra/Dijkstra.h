#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "../Graph.h"

namespace aod {

	struct Node {
		std::shared_ptr<Node> parent_node;
		int node;
		int distance;
	};

	struct NodeComparator {
		bool operator() (std::shared_ptr<Node>& node1, std::shared_ptr<Node>& node2) {
			return node1->distance > node2->distance;
		}
	};

	std::vector<int> dijkstra(Graph& graph, int from, int to);
	std::vector<int> dijkstraWithOnlyDistances(Graph& graph, int src);
}
