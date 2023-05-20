#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <queue>
#include <bitset>

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
			: path_element(0), node(node), distance(distance) {}

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
		std::vector<std::priority_queue<Node, std::vector<Node>, NodeComparator>> buckets;
		unsigned int min_value;

		RadixHeap() : buckets(32), min_value(std::numeric_limits<unsigned int>::max()) {}

		void push(Node x) {
			unsigned int key = x.distance;
			std::bitset<32> test{ key };
			int nearest_pow_of_two = 31;
			while (nearest_pow_of_two > 0 && test[nearest_pow_of_two] != 1) --nearest_pow_of_two;
			min_value = std::min(min_value, key);
			buckets[nearest_pow_of_two].push(x);
		}

		Node pop() {
			unsigned int i = min_value;
			while (buckets[i].empty()) {
				++i;
			}
			min_value = i;
			const Node res = buckets[i].top();
			buckets[i].pop();
			return res;
		}

		bool empty() const {
			for (const auto& bucket : buckets) {
				if (!bucket.empty())
					return false;
			}
			return true;
		}
	};

	unsigned int findMaxWeightInGraph(const Graph& graph);

	std::vector<unsigned int> dijkstra(Graph& graph, unsigned int from, unsigned int to);
	std::vector<unsigned int> dijkstraWithOnlyDistances(Graph& graph, unsigned int src);

	std::vector<unsigned int> dijkstraDial(Graph& graph, unsigned int from, unsigned int to);
	std::vector<unsigned int> dijkstraDialWithOnlyDistances(Graph& graph, unsigned int src);

	std::vector<unsigned int> dijkstraRadix(Graph& graph, unsigned int from, unsigned int to);
	std::vector<unsigned int> dijkstraRadixWithOnlyDistances(Graph& graph, unsigned int s);
}
