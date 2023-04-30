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

	std::vector<int> dijkstraDial(Graph& graph, int src, int W) {

		auto& [n, m, adjacency_list] = graph;

		std::vector<std::pair<int, std::list<int>::iterator>> dist(n + 1);
	 
	    for (int i = 0; i <= n; i++)
	        dist[i].first = std::numeric_limits<int>::max();
	 
		std::vector<std::list<int>> buckets(W * n + 1);

	    buckets[0].push_back(src);
	    dist[src].first = 0;
	 
	    int idx = 0;
	    while (true) {
	        while (buckets[idx].empty() && idx < W*n)
	            idx++;
	 
	        if (idx == W * n)
	            break;
	 
	        int u = buckets[idx].front();
	        buckets[idx].pop_front();
	 
	        for (const auto& [v, weight] : adjacency_list[u]) {

	            int dv = dist[v].first;
	            int du = dist[u].first;
	 
	            if (dv > du + weight) {
	                if (dv != std::numeric_limits<int>::max())
	                    buckets[dv].erase(dist[v].second);
	 
	                dist[v].first = du + weight;
	                dv = dist[v].first;
	 
	                buckets[dv].push_front(v);
	 
	                dist[v].second = buckets[dv].begin();
	            }
	        }
	    }
	 
	    std::vector<int> distances(n + 1);
		std::ranges::transform(
			dist.begin(),
			dist.end(),
			distances.begin(),
			[&] (const std::pair<int, std::list<int>::iterator>& el) -> int { return el.first; });

		return distances;
	}
}