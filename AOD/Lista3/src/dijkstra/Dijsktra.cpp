#include <iostream>
#include <queue>

#include "Dijkstra.h"

namespace aod {

	std::vector<int> dijkstra(Graph& graph, int from, int to) {

		auto& [n, m, adjacency_list] = graph;

		std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparator> pq;
		const auto src_node = std::make_shared<Node>(nullptr, from, 0);
		pq.push(src_node);

		while (!pq.empty()) {
	        auto current_node = pq.top();
	        pq.pop();

			const auto& [parent_node, node, distance] = *current_node;

	        if (node == to) {

				std::vector<int> path;
				while (current_node != nullptr) {
					path.push_back(current_node->node);
					current_node = current_node->parent_node;
				}

				std::ranges::reverse(path);

	            return path;
	        }

	        for (const auto& [v, w] : adjacency_list[node]) {
	        	pq.push(std::make_shared<Node>(current_node, v, distance + w));
	        }
	    }
	}

	std::vector<int> dijkstraWithOnlyDistances(Graph& graph, int src) {

		auto& [n, m, adjacency_list] = graph;

		constexpr int inf = std::numeric_limits<int>::max();
		std::vector<int> dist(n + 1, inf);

		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

		dist[src] = 0;
		pq.push({ 0, src });

		while (!pq.empty()) {
			const auto [d, u] = pq.top();
			pq.pop();

			if (d > dist[u]) continue;

			for (const auto& [v, w] : adjacency_list[u]) {
				if (dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					pq.push({ dist[v], v});
				}
			}
		}

		return dist;
	}
}