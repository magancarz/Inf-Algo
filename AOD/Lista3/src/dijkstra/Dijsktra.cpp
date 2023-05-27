#include <iostream>
#include <queue>
#include <ranges>
#include <map>

#include "Dijkstra.h"

#define DEBUG 0

namespace aod {

	unsigned int findMaxWeightInGraph(Graph& graph) {

		int max_weight = 0;
		for (const auto& node : std::ranges::views::iota(1, static_cast<int>(graph.v))) {
			for (const auto& [v, weight] : graph.adjacency_list[node]) {
				max_weight = std::max(max_weight, weight);
			}
		}

		return max_weight;
	}

	unsigned int dijkstra(Graph& graph, unsigned int from, unsigned int to)
	{
		auto& [n, m, adjacency_list] = graph;

		std::vector<uint64_t> distances(n + 1, std::numeric_limits<uint64_t>::max());
		distances[from] = 0;
		std::priority_queue<Node, std::vector<Node>, NodeComparator> q;
		q.push(Node(0, from, 0));

		while (!q.empty())
		{
			auto x = q.top();
			q.pop();

			if (x.node == to)
			{
				return x.path_iter;
			}

			if (x.distance != distances[x.node]) continue;

			for (const auto& e : adjacency_list[x.node]) {
				if (distances[e.first] > distances[x.node] + e.second) {
					distances[e.first] = distances[x.node] + e.second;

					q.push(Node(x.path_iter + 1, e.first, distances[e.first]));
				}
			}
		}
	}

	std::vector<unsigned int> dijkstraWithOnlyDistances(Graph& graph, unsigned int src)
	{
		auto& [n, m, adjacency_list] = graph;

		std::vector<unsigned int> dist(n + 1, std::numeric_limits<unsigned int>::max());

		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

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
					if (dist[v] + w >= std::numeric_limits<uint64_t>::max()) std::cout << "Damn\n";
					dist[v] = dist[u] + w;
					pq.push({ dist[v], v});
				}
			}
		}

		return dist;
	}

	unsigned int dijkstraDial(Graph& graph, unsigned int from, unsigned int to) {

		auto& [n, m, adjacency_list] = graph;

		std::vector<unsigned int> dist(n + 1, std::numeric_limits<unsigned int>::max());
	 
		std::map<unsigned int, std::priority_queue<Node, std::vector<Node>, NodeComparator>> buckets;

	    buckets[0].push(Node(0, from, 0));
	    dist[from] = 0;

	    unsigned int idx = 0;
	    while (true) {
			auto it = buckets.begin();
			if (it == buckets.end()) break;
			idx = (*it).first;
			if (buckets[idx].empty()) {
				buckets.erase(idx);
				continue;
			}
	 
	        auto u = buckets[idx].top();
	        buckets[idx].pop();

			if (u.node == to) {
	            return u.path_iter;
	        }

	        for (const auto& [v, weight] : adjacency_list[u.node])
			{
	            const unsigned int du = dist[u.node];
	            unsigned int dv = dist[v];
	 
	            if (du + weight < dv)
				{
	                dist[v] = du + weight;
	                dv = dist[v];

	                buckets[dv].push(Node(u.path_iter + 1, v, du + weight));
	            }
	        }
	    }
	}

	std::vector<unsigned int> dijkstraDialWithOnlyDistances(Graph& graph, unsigned int src)
	{
		auto& [n, m, adjacency_list] = graph;
		std::vector<unsigned int> dist(graph.v + 1, std::numeric_limits<unsigned int>::max());

		std::map<unsigned int, std::list<unsigned int>> buckets;

		auto max_weight = findMaxWeightInGraph(graph);
#if DEBUG 1
		std::cout << "Running dial algorithm with "
			<< n << " vertices, "
			<< m << " edges and with max weight C of "
			<< max_weight << ".\n";
#endif

		dist[src] = 0;
		buckets[0].push_back(src);

		unsigned int current_bucket = 0;
		while (true)
		{
			auto it = buckets.begin();
			if (it == buckets.end()) break;
			current_bucket = (*it).first;
			if (buckets[current_bucket].empty()) {
				buckets.erase(current_bucket);
				continue;
			}

			unsigned int u = buckets[current_bucket].front();
			buckets[current_bucket].pop_front();

			for (const auto& [v, w] : adjacency_list[u]) {
				const unsigned int du = dist[u];
				const unsigned int dv = dist[v];

				if (du + w < dv)
				{
					if (dv != std::numeric_limits<unsigned int>::max())
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

	unsigned int dijkstraRadix(Graph& graph, unsigned int from, unsigned int to)
	{
		auto& [n, m, adjacency_list] = graph;

		std::vector<uint64_t> distances(n + 1, std::numeric_limits<uint64_t>::max());
	    distances[from] = 0;
	    std::unique_ptr<RadixHeap> q = std::make_unique<RadixHeap>();
	    q->push(Node(0, from, 0));

	    while (!q->empty()) {
	        auto x = q->pop();

			if (x.node == to) {
	            return x.node;
	        }

	        if (x.distance != distances[x.node]) continue;

	        for (const auto& e : adjacency_list[x.node]) {
	            if (distances[e.first] > distances[x.node] + e.second) {
					if (distances[x.node] + e.second >= std::numeric_limits<uint64_t>::max()) std::cout << "Damn\n";
	                distances[e.first] = distances[x.node] + e.second;

	                q->push(Node(x.path_iter + 1, e.first, distances[e.first]));
	            }
	        }
	    }
	}

	std::vector<unsigned int> dijkstraRadixWithOnlyDistances(Graph& graph, unsigned int s)
	{
		auto& [n, m, adjacency_list] = graph;
		const unsigned int max_weight = findMaxWeightInGraph(graph);

		std::vector<unsigned int> distances(n + 1, std::numeric_limits<unsigned int>::max());
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