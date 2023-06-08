#include <bitset>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
#include <chrono>

struct Edge
{
    int source;
    int target;
    int capacity;
    int flow;
    Edge* reverse;

    Edge(int source, int target, int capacity)
        : source(source), target(target), capacity(capacity), flow(0), reverse(nullptr) {}
};

bool differByOneBit(int num1, int num2) {
    int xorResult = num1 ^ num2;
    int bitCount = 0;

    while (xorResult != 0) {
        if ((xorResult & 1) == 1) {
            bitCount++;
            if (bitCount > 1) {
                return false;
            }
        }
        xorResult >>= 1;
    }

    return bitCount == 1;
}

using Graph = std::vector<std::vector<Edge*>>;

Graph generateHypercubeGraph(int k)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> random(0.0, 1.0);
    Graph graph(pow(2, k));
    
    for (int vertex = 0; vertex < graph.size(); ++vertex)
    {
        std::bitset<32> vertex_bin(vertex);
        int vertex_one_count = vertex_bin.count();
        
        for (int other_vertex = 0; other_vertex < graph.size(); ++other_vertex)
        {
            auto it = std::find_if(graph[vertex].begin(), graph[vertex].end(), [&] (const Edge* edge)
            {
                return edge->source == vertex && edge->target == other_vertex; 
            });
            
            if (it != graph[vertex].end())
                continue;
            
            std::bitset<32> other_vertex_bin(other_vertex);
            const auto should_be_edge = differByOneBit(vertex, other_vertex);
            
            if (should_be_edge)
            {
                int other_vertex_one_count = other_vertex_bin.count();
                
                if (other_vertex_one_count > vertex_one_count)
                {
                    int random_flow_capacity = static_cast<int>(random(rng) * 100.0);
                    
                    Edge* edge = new Edge(vertex, other_vertex, 0);
                    graph[vertex].push_back(edge);
                    
                    Edge* reverse_edge = new Edge(other_vertex, vertex, random_flow_capacity);
                    edge->reverse = reverse_edge;
                    reverse_edge->reverse = edge;
                    graph[other_vertex].push_back(reverse_edge);
                }
            }
        }
    }
    
    return graph;
}

Graph generateRandomBipartiteGraph(int k, int i)
{
    int graph_size = (1 << k);
    Graph graph(graph_size * 2 + 2);
    std::vector<int> V1(graph_size);
    std::vector<int> V2(graph_size);

    for (int j = 1; j <= graph_size; ++j)
        V1[j - 1] = j;
    for (int j = 1; j <= graph_size; ++j)
        V2[j - 1] = j + graph_size;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> random(0.0, 1.0);
	std::ranges::shuffle(V2.begin(), V2.end(), rng);

    for (int j = 0; j < graph_size; ++j)
    {
        for (int l = 0; l < i; ++l)
        {
            const int source = V1[j];
            int target;
            auto edge_exist = std::vector<Edge*>::iterator();
        	do
            {
        		target = V2[static_cast<int>(random(rng) * (V2.size() - 1))];
                edge_exist = std::find_if(graph[source].begin(), graph[source].end(), [&](const Edge* edge)
        		{
        			return edge->source == source && edge->target == target;
        		});
            }
        	while(edge_exist != graph[source].end());

            Edge* edge = new Edge{source, target, 1};
            graph[j + 1].push_back(edge);

           // std::cout << "Edge from " << source << " to " << target << std::endl;

        	Edge* reverse_edge = new Edge{target, source, 0};
            reverse_edge->reverse = edge;
            edge->reverse = reverse_edge;
            graph[target].push_back(reverse_edge);
        }
    }

    for (int j = 0; j < graph_size; ++j)
    {
        const int source = 0;
        const int target = V1[j];

        Edge* edge = new Edge{source, target, 1};
        graph[source].push_back(edge);

        Edge* reverse_edge = new Edge{target, source, 0};
        reverse_edge->reverse = edge;
        edge->reverse = reverse_edge;
        graph[target].push_back(reverse_edge);
    }

    for (int j = 0; j < graph_size; ++j)
    {
        const int source = V2[j];
        const int target = graph_size * 2 + 1;

        Edge* edge = new Edge{source, target, 1};
        graph[source].push_back(edge);

        Edge* reverse_edge = new Edge{target, source, 0};
        reverse_edge->reverse = edge;
        edge->reverse = reverse_edge;
        graph[target].push_back(reverse_edge);
    }

    return graph;
}

int EdmondsKarp(Graph& graph, int source, int sink)
{
    int flow = 0;
    const auto num_vertices = graph.size();
    int road_counter = 0;

    while (true)
    {
        std::vector<Edge*> pred(num_vertices, nullptr);
        std::queue<int> queue;
        queue.push(source);

        while (!queue.empty()) 
        {
            const int current = queue.front();
            queue.pop();

            for (Edge* edge : graph[current])
            {
                if (pred[edge->target] == nullptr && edge->target != source && edge->capacity > edge->flow) 
                {
                    pred[edge->target] = edge;
                    queue.push(edge->target);
                }
            }
        }

        if (pred[sink] != nullptr)
        {
            int df = std::numeric_limits<int>::max();
            for (Edge* e = pred[sink]; e != nullptr; e = pred[e->source])
            {
                df = std::min(df, e->capacity - e->flow);
            }

            for (Edge* e = pred[sink]; e != nullptr; e = pred[e->source])
            {
                e->flow += df;
                e->reverse->flow -= df;
            }

            flow += df;
            ++road_counter;
        }
    	else
        {
            std::cerr << "Number of augmenting paths: " << road_counter << std::endl;
            break;
        }
    }

    return flow;
}

int main()
{
    /*int k = 2;
    int num_vertices = pow(2, k);
    Graph graph = generateHypercubeGraph(k);

    int source = num_vertices - 1;
    int sink = 0;
    const auto start = std::chrono::steady_clock::now();
    int maxFlow = EdmondsKarp(graph, source, sink);
    const auto end = std::chrono::steady_clock::now();
    std::cerr << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

    std::cout << "Max Flow: " << maxFlow << std::endl;
    for (int i = 0; i < graph.size(); ++i)
    {
        for (const Edge* edge : graph[i])
        {
            std::bitset<32> vertex_one_count(edge->source);
            std::bitset<32> other_vertex_one_count(edge->target);
            if (vertex_one_count.count() < other_vertex_one_count.count()) std::cout << "Edge from " << edge->source << " to " << edge->target << " has flow of " << -edge->flow << std::endl;
        }
    }*/

    int k = 10;
    int num_vertices = 1 << k;
    Graph graph = generateRandomBipartiteGraph(k, 7);

    const auto start = std::chrono::steady_clock::now();
    int result = EdmondsKarp(graph, 0, num_vertices * 2 + 1);
    const auto end = std::chrono::steady_clock::now();
    std::cerr << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    int maximum_matching_set_count = 0;
    for (int i = 1; i <= num_vertices; ++i)
    {
	    for (const auto edge : graph[i])
	    {
		    if (edge->flow > 0)
		    {
				//std::cout << "Edge from " << edge->source << " to " << edge->target << " belong to maximum matching set\n";
                ++maximum_matching_set_count;
		    }
	    }
    }
    std::cerr << "Size of maximum matching set is " << maximum_matching_set_count << std::endl;

    for (int i = 0; i < num_vertices; ++i)
    {
        for (Edge* edge : graph[i])
        {
            delete edge;
        }
    }

    return 0;
}