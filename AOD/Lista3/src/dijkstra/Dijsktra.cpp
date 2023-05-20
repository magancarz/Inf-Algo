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

	std::vector<unsigned int> dijkstra(Graph& graph, unsigned int from, unsigned int to) {

		auto& [n, m, adjacency_list] = graph;

		std::vector<bool> visited_nodes(n + 1, false);
		std::priority_queue<Node, std::vector<Node>, NodeComparator> pq;
		pq.push(Node(0, from, 0));

		path_elements.push_back({ 0, from });
		uint64_t path_element_idx = 1;

		while (!pq.empty()) {
	        const auto [path_element, node, distance] = pq.top();
	        pq.pop();

			if (visited_nodes[node]) {
				continue;
			}

			visited_nodes[node] = true;

			if (node == to) {
				std::vector<unsigned int> path;

				uint64_t current_path_element = path_element;
				while (current_path_element != 0) {
					path.push_back(path_elements[current_path_element].node);
					current_path_element = path_elements[current_path_element].parent;
				}

				path.push_back(from);

				std::ranges::reverse(path);

				path_elements.clear();

	            return path;
	        }

	        for (const auto& [v, w] : adjacency_list[node]) {
				path_elements.push_back(PathElement(path_element, v));
	        	pq.push(Node(path_element_idx, v, distance + w));
				++path_element_idx;
	        }
	    }

		return {};
	}

	std::vector<unsigned int> dijkstraWithOnlyDistances(Graph& graph, unsigned int src) {

		auto& [n, m, adjacency_list] = graph;

		constexpr int inf = std::numeric_limits<unsigned int>::max();
		std::vector<unsigned int> dist(n + 1, inf);

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

	std::vector<unsigned int> dijkstraDial(Graph& graph, unsigned int from, unsigned int to) {

		auto& [n, m, adjacency_list] = graph;
		const unsigned int max_weight = findMaxWeightInGraph(graph);

		std::vector<std::pair<unsigned int, std::list<Node>::iterator>> dist(n + 1);
	 
	    for (int i = 0; i <= n; i++) {
	        dist[i].first = std::numeric_limits<unsigned int>::max();
	    }

		std::map<unsigned int, std::list<Node>> buckets;

	    buckets[0].push_back(Node(0, from, 0));
	    dist[from].first = 0;

		path_elements.push_back({ 0, from });
		uint64_t path_element_idx = 1;
	 
	    unsigned int idx = 0;
	    while (true) {
			auto it = buckets.begin();
			if (it == buckets.end()) break;
			idx = (*it).first;
			if (buckets[idx].empty()) {
				buckets.erase(idx);
				continue;
			}
	 
	        auto u = buckets[idx].front();
	        buckets[idx].pop_front();

			if (u.node == to) {
				std::vector<unsigned int> path;

				uint64_t current_path_element = u.path_element;
				while (current_path_element != 0) {
					path.push_back(path_elements[current_path_element].node);
					current_path_element = path_elements[current_path_element].parent;
				}

				path.push_back(from);

				std::ranges::reverse(path);

				path_elements.clear();

	            return path;
	        }

	        for (const auto& [v, weight] : adjacency_list[u.node]) {

	            const unsigned int du = dist[u.node].first;
	            unsigned int dv = dist[v].first;
	 
	            if (du + weight < dv) {
	                if (dv != std::numeric_limits<unsigned int>::max())
	                    buckets[dv].erase(dist[v].second);
	 
	                dist[v].first = du + weight;
	                dv = dist[v].first;

					path_elements.push_back(PathElement(u.path_element, v));
	                buckets[dv].push_front(Node(path_element_idx, v, du + weight));
					++path_element_idx;

	                dist[v].second = buckets[dv].begin();
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

			if (current_bucket % 1000000 == 0) 
			{
				std::cout << "Bucket no. " << current_bucket << std::endl;
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

	std::vector<unsigned int> dijkstraRadix(Graph& graph, unsigned int from, unsigned int to) {

		auto& [n, m, adjacency_list] = graph;
		const unsigned int max_weight = findMaxWeightInGraph(graph);

		std::vector<unsigned int> distances(n + 1, std::numeric_limits<unsigned int>::max());
	    distances[from] = 0;
	    std::unique_ptr<RadixHeap> q = std::make_unique<RadixHeap>();
	    q->push(Node(0, from, 0));

		path_elements.push_back({ 0, from });
		uint64_t path_element_idx = 1;

	    while (!q->empty()) {
	        auto x = q->pop();

			if (x.node == to) {
				std::vector<unsigned int> path;

				uint64_t current_path_element = x.path_element;
				while (current_path_element != 0) {
					path.push_back(path_elements[current_path_element].node);
					current_path_element = path_elements[current_path_element].parent;
				}

				path.push_back(from);

				std::ranges::reverse(path);

				path_elements.clear();

	            return path;
	        }

	        if (x.distance != distances[x.node]) continue;

	        for (const auto& e : adjacency_list[x.node]) {
	            if (distances[e.first] > distances[x.node] + e.second) {
	                distances[e.first] = distances[x.node] + e.second;

					path_elements.push_back(PathElement(x.path_element, e.first));
	                q->push(Node(path_element_idx, e.first, distances[e.first]));
					++path_element_idx;
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