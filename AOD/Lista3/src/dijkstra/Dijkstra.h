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
		bool operator() (const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2) const {
			return node1->distance > node2->distance;
		}
	};

	std::vector<int> dijkstra(Graph& graph, int from, int to);
	std::vector<int> dijkstraWithOnlyDistances(Graph& graph, int src);

	std::vector<int> dijkstraDial(Graph& graph, int from, int to, int W);
	std::vector<int> dijkstraDialWithOnlyDistances(Graph& graph, int src, int W);
}
