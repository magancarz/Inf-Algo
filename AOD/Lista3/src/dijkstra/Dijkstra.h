#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <bit>

#include "../Graph.h"

namespace aod {

	struct Node {
		std::shared_ptr<Node> parent_node;
		int node;
		unsigned int distance;

		Node() = default;
		Node(int node, unsigned int distance)
			: node(node), distance(distance) {
			parent_node = nullptr;
		}

		Node(std::shared_ptr<Node> parent_node, int node, unsigned int distance)
			: parent_node(std::move(parent_node)), node(node), distance(distance) {}

		bool operator<(const Node& other) const {
			return distance > other.distance;
		}
	};

	struct NodeComparator {
		bool operator() (const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2) const {
			return node1->distance > node2->distance;
		}
	};

	struct RadixHeap {
		std::vector<std::vector<std::shared_ptr<Node>>> buckets;
	    int last = 0;

		RadixHeap(unsigned int n, unsigned int max_weight) {
			buckets = std::vector<std::vector<std::shared_ptr<Node>>>(n * max_weight + 1);
		}

	    void push(const std::shared_ptr<Node>& x) {
	        buckets[x->distance].push_back(x);
	    }

	    std::shared_ptr<Node> pop() {
	        int i = 0;
	        while (buckets[i].empty()) ++i;
	        int j = 0;
	        for (int k = 1; k < buckets[i].size(); ++k) {
	            if (buckets[i][k]->distance < buckets[i][j]->distance) j = k;
	        }
	        const std::shared_ptr<Node> res = buckets[i][j];
	        buckets[i].erase(buckets[i].begin() + j);
	        last = res->distance;
	        return res;
	    }

	    bool empty() {
			return std::ranges::all_of(buckets.begin(), buckets.end(), [] (const std::vector<std::shared_ptr<Node>>& bucket) { return bucket.empty(); });
	    }
	};


	std::vector<int> dijkstra(Graph& graph, int from, int to);
	std::vector<int> dijkstraWithOnlyDistances(Graph& graph, int src);

	std::vector<int> dijkstraDial(Graph& graph, int from, int to, int max_weight);
	std::vector<int> dijkstraDialWithOnlyDistances(Graph& graph, int src, int max_weight);

	std::vector<int> dijkstraRadix(Graph& graph, int from, int to, int max_weight);
	std::vector<int> dijkstraRadixWithOnlyDistances(Graph& graph, int s, int max_weight);
}
