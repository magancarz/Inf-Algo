#include <iostream>
#include <queue>
#include <ranges>
#include <map>
#include <list>

#include "Dijkstra.h"

namespace aod {

	uint64_t findMaxWeightInGraph(Graph& graph)
	{
		int max_weight = 0;
		for (const auto& node : std::ranges::views::iota(1, static_cast<int>(graph.v)))
		{
			for (const auto& [v, weight] : graph.adjacency_list[node])
			{
				max_weight = std::max(max_weight, weight);
			}
		}

		return static_cast<uint64_t>(max_weight);
	}

	uint64_t findMinWeightInGraph(Graph& graph)
	{
		int max_weight = std::numeric_limits<int>::max();
		for (const auto& node : std::ranges::views::iota(1, static_cast<int>(graph.v)))
		{
			for (const auto& [v, weight] : graph.adjacency_list[node])
			{
				max_weight = std::min(max_weight, weight);
			}
		}

		return max_weight;
	}

	uint64_t dijkstra(Graph& graph, unsigned int from, unsigned int to)
	{
		auto& [n, m, adjacency_list] = graph;

		std::vector<uint64_t> distances(n + 1, std::numeric_limits<uint64_t>::max());
		distances[from] = 0;
		std::priority_queue<Node, std::vector<Node>, NodeComparator> q;
		q.push(Node(0, from, 0));

		std::unordered_map<unsigned int, bool> visited_nodes(graph.m);

		while (!q.empty())
		{
			auto x = q.top();
			q.pop();

			visited_nodes[x.node] = true;

			if (x.node == to)
			{
				return x.path_iter;
			}

			if (x.distance != distances[x.node]) continue;

			for (const auto& e : adjacency_list[x.node]) {
				if (!visited_nodes.contains(e.first) && distances[e.first] > distances[x.node] + e.second) {
					distances[e.first] = distances[x.node] + e.second;

					q.push(Node(x.path_iter + e.second, e.first, distances[e.first]));
				}
			}
		}
	}

	std::vector<uint64_t> dijkstraWithOnlyDistances(Graph& graph, unsigned int src)
	{
		auto& [n, m, adjacency_list] = graph;

		std::vector<uint64_t> dist(n + 1, std::numeric_limits<uint64_t>::max());

		std::priority_queue<std::pair<uint64_t, uint64_t>, std::vector<std::pair<uint64_t, uint64_t>>, std::greater<>> pq;

		dist[src] = 0;
		pq.push({ 0, src });

		while (!pq.empty())
		{
			const auto [d, u] = pq.top();
			pq.pop();

			if (d > dist[u]) continue;

			for (const auto& [v, w] : adjacency_list[u])
			{
				if (dist[u] + w < dist[v])
				{
					dist[v] = dist[u] + w;
					pq.push({ dist[v], v});
				}
			}
		}

		return dist;
	}

	uint64_t dijkstraDial(Graph& graph, unsigned int from, unsigned int to) {

		auto& [n, m, adjacency_list] = graph;

		std::vector<uint64_t> dist(n + 1, std::numeric_limits<uint64_t>::max());
	 
		std::map<uint64_t, std::priority_queue<Node, std::vector<Node>, NodeComparator>> buckets;

	    buckets[0].push(Node(0, from, 0));
	    dist[from] = 0;

		std::unordered_map<unsigned int, bool> visited_nodes(graph.m);

	    unsigned int idx = 0;
	    while (true)
		{
			auto it = buckets.begin();
			if (it == buckets.end()) break;
			idx = (*it).first;
			if (buckets[idx].empty())
			{
				buckets.erase(idx);
				continue;
			}
	 
	        auto u = buckets[idx].top();
	        buckets[idx].pop();

			visited_nodes[u.node] = true;

			if (u.node == to) 
			{
	            return u.path_iter;
	        }

	        for (const auto& [v, weight] : adjacency_list[u.node])
			{
	            const uint64_t du = dist[u.node];
	            uint64_t dv = dist[v];
	 
	            if (!visited_nodes.contains(v) && du + weight < dv)
				{
	                dist[v] = du + weight;
	                dv = dist[v];

	                buckets[dv].push(Node(u.path_iter + weight, v, du + weight));
	            }
	        }
	    }
	}

	std::vector<uint64_t> dijkstraDialWithOnlyDistances(Graph& graph, unsigned int src)
	{
		auto& [n, m, adjacency_list] = graph;
		std::vector<uint64_t> dist(graph.v + 1, std::numeric_limits<uint64_t>::max());

		std::map<uint64_t, std::list<uint64_t>> buckets;

		dist[src] = 0;
		buckets[0].push_back(src);

		uint64_t current_bucket = 0;
		while (true)
		{
			auto it = buckets.begin();
			if (it == buckets.end()) break;
			current_bucket = (*it).first;
			if (buckets[current_bucket].empty()) {
				buckets.erase(current_bucket);
				continue;
			}

			uint64_t u = buckets[current_bucket].front();
			buckets[current_bucket].pop_front();

			for (const auto& [v, w] : adjacency_list[u]) {
				const uint64_t du = dist[u];
				const uint64_t dv = dist[v];

				if (du + w < dv)
				{
					if (dv != std::numeric_limits<uint64_t>::max())
					{
						buckets[dv].erase(std::find(buckets[dv].begin(), buckets[dv].end(), v));
					}
					dist[v] = du + w;
					buckets[dist[v]].push_front(v);
				}
			}
		}

		return dist;
	}

	uint64_t dijkstraRadix(Graph& graph, unsigned int from, unsigned int to)
	{
		auto& [n, m, adjacency_list] = graph;

		auto max_weight = findMaxWeightInGraph(graph);

		std::vector<uint64_t> distances(n + 1, std::numeric_limits<uint64_t>::max());
		distances[from] = 0;
		RadixHeap q;
		q.push(Node(0, from, 0));

		std::unordered_map<unsigned int, bool> visited_nodes(graph.m);

		while (!q.empty())
		{
			auto x = q.pop();

			visited_nodes[x.node] = true;

			if (x.node == to)
			{
				return x.path_iter;
			}

			if (x.distance != distances[x.node]) continue;

			for (const auto& e : adjacency_list[x.node]) {
				if (!visited_nodes.contains(e.first) && distances[e.first] > distances[x.node] + e.second) {
					distances[e.first] = distances[x.node] + e.second;

					q.push(Node(x.path_iter + e.second, e.first, distances[e.first]));
				}
			}
		}
	}

	std::vector<uint64_t> dijkstraRadixWithOnlyDistances(Graph& graph, unsigned int s)
	{
		auto& [n, m, adjacency_list] = graph;
		const uint64_t max_weight = findMaxWeightInGraph(graph);

		std::vector<uint64_t> distances(n + 1, std::numeric_limits<uint64_t>::max());
	    distances[s] = 0;
	    RadixHeap q;
	    q.push(Node(0, s, 0));
	    while (!q.empty())
		{
	        auto x = q.pop();

	        if (x.distance != distances[x.node]) continue;
			for (const auto& e : adjacency_list[x.node])
			{
				if (distances[e.first] > x.distance + e.second)
				{
					distances[e.first] = x.distance + e.second;
					q.push(Node(0, e.first, distances[e.first]));
				}
			}
	    }
		
	    return distances;
	}
}