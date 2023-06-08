#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <queue>
#include <bitset>
#include <numeric>

#include "../Graph.h"

namespace aod {

	struct Node {
		uint64_t path_iter;
		uint64_t node;
		uint64_t distance;

		Node() = default;
		Node(uint64_t node, uint64_t distance)
			: path_iter(0), node(node), distance(distance) {}

		Node(uint64_t path_iter, uint64_t node, uint64_t distance)
			: path_iter(path_iter), node(node), distance(distance) {}

		bool operator<(const Node& other) const {
			return distance > other.distance;
		}
	};

	struct NodeComparator {
		bool operator() (const Node& node1, const Node& node2) const {
			return node1.distance > node2.distance;
		}
	};

	struct RadixHeap
	{
		std::vector<std::priority_queue<Node, std::vector<Node>, NodeComparator>> buckets;
		uint64_t min_value;

		RadixHeap() : buckets(32), min_value(std::numeric_limits<uint64_t>::max()) {}

		void push(Node x)
		{
			uint64_t key = x.distance;
			std::bitset<32> test{ key };
			int nearest_pow_of_two = 31;
			while (nearest_pow_of_two > 0 && test[nearest_pow_of_two] != 1) --nearest_pow_of_two;
			min_value = std::min(min_value, key);
			buckets[nearest_pow_of_two].push(x);
		}

		Node pop()
		{
			uint64_t i = 0;
			while (buckets[i].empty()) ++i;
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

	uint64_t findMaxWeightInGraph(Graph& graph);
	uint64_t findMinWeightInGraph(Graph& graph);

	uint64_t dijkstra(Graph& graph, unsigned int from, unsigned int to);
	std::vector<uint64_t> dijkstraWithOnlyDistances(Graph& graph, unsigned int src);

	uint64_t dijkstraDial(Graph& graph, unsigned int from, unsigned int to);
	std::vector<uint64_t> dijkstraDialWithOnlyDistances(Graph& graph, unsigned int src);

	uint64_t dijkstraRadix(Graph& graph, unsigned int from, unsigned int to);
	std::vector<uint64_t> dijkstraRadixWithOnlyDistances(Graph& graph, unsigned int s);
}
