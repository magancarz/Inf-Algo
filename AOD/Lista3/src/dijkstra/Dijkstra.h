#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <queue>

#include "../Graph.h"

namespace aod {

	struct PathElement {
		uint64_t parent;
		unsigned int node;
	};

	inline std::vector<PathElement> path_elements;

	struct Node {
		uint64_t path_element;
		unsigned int node;
		unsigned int distance;

		Node() = default;
		Node(int node, unsigned int distance)
			: node(node), distance(distance) {}

		Node(uint64_t path_element, int node, unsigned int distance)
			: path_element(path_element), node(node), distance(distance) {}

		bool operator<(const Node& other) const {
			return distance > other.distance;
		}
	};

	struct NodeComparator {
		bool operator() (const Node& node1, const Node& node2) const {
			return node1.distance > node2.distance;
		}
	};

	struct RadixHeap {
		std::unordered_map<unsigned int, std::list<Node>> buckets;

	    void push(Node x) {
	        buckets[x.distance].push_back(x);
	    }

	    Node pop() {
	        unsigned int i = 0;
	        while (buckets[i].empty()) ++i;
	        const Node res = buckets[i].front();
			buckets[i].pop_front();
	        return res;
	    }

	    bool empty() {
			return std::ranges::all_of(buckets.begin(), buckets.end(), [] (const std::pair<unsigned int, std::list<Node>>& bucket) { return bucket.second.empty(); });
	    }
	};

	unsigned int findMaxWeightInGraph(Graph& graph);

	std::vector<unsigned int> dijkstra(Graph& graph, unsigned int from, unsigned int to);
	std::vector<unsigned int> dijkstraWithOnlyDistances(Graph& graph, unsigned int src);

	std::vector<unsigned int> dijkstraDial(Graph& graph, unsigned int from, unsigned int to);
	std::vector<unsigned int> dijkstraDialWithOnlyDistances(Graph& graph, unsigned int src);

	std::vector<unsigned int> dijkstraRadix(Graph& graph, unsigned int from, unsigned int to);
	std::vector<unsigned int> dijkstraRadixWithOnlyDistances(Graph& graph, unsigned int s);
}
