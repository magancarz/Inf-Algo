#include "Graph.h"

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <ranges>
#include <unordered_map>

void Graph::operator=(const Graph& other) {
    is_directed = other.is_directed;
    n = other.n;
    m = other.m;
    vertices = other.vertices;
}

void Graph::loadDataFromFileToGraph(const std::string& path) {

	std::ifstream file_stream(path);
	if (file_stream.is_open()) {
		std::string line;
		getline(file_stream, line);
		if (line[0] == 'D') {
            is_directed = true;
		}

		getline(file_stream, line);
        n = std::stoi(line);

		getline(file_stream, line);
        m = std::stoi(line);

		while (getline(file_stream, line)) {
			std::istringstream iss(line);
			std::string u, v;
			iss >> u;
			iss >> v;

            vertices[std::stoi(u)].push_back(std::stoi(v));
		}

		file_stream.close();
	} else {
		std::cout << "Unable to open file!\n_";
	}
}

void Graph::DFS(bool print_tree) {
	resetVisitedVertices();
	tree.clear();

	DFS(1);

	if (print_tree) {
		printTree();
	}
}

void Graph::DFS(int v) {
    visited[v] = true;
	std::cout << v << std::endl;
	
	for (auto& i : vertices[v]) {
		if (!visited[i]) {
			DFS(i);
			tree[v].push_back(i);
		}
	}
}

void Graph::BFS(bool print_tree) {
	resetVisitedVertices();
	tree.clear();

	std::list<int> queue;

    visited[1] = true;
	queue.push_back(1);

	int v;
	while (!queue.empty()) {
        v = queue.front();
		queue.pop_front();
		std::cout << v << std::endl;

		for (const auto& adjacent : vertices[v]) {
			if(!visited[adjacent]) {
                visited[adjacent] = true;
				queue.push_back(adjacent);
				tree[v].push_back(adjacent);
			}
		}
	}

	if (print_tree) {
		printTree();
	}
}

void Graph::printTree() {
	for (auto& v : tree) {
		std::cout << v.first << " -> ";

		for (int i = 0; i < v.second.size(); ++i) {
			if (i < v.second.size() - 1) {
				std::cout << v.second[i] << ", ";
			} else {
				std::cout << v.second[i] << "\n";
			}
		}
	}
}

void Graph::topologicalSort() {
    resetVisitedVertices();

    std::stack<std::pair<bool, int>> dfs;
    std::stack<int> post_order;

    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) {
            dfs.emplace(false, v);
        }

        while (!dfs.empty()) {
            std::pair<bool, int> node = dfs.top();
            dfs.pop();

            if (node.first) {
                post_order.push(node.second);
                continue;
            }

            if (visited[node.second]) {
                continue;
            }

            visited[node.second] = true;
            dfs.emplace(true, node.second);
            const auto& adjacents = vertices[node.second];
            for (const auto adjacent : adjacents) {
                if (!visited[adjacent]) {
                    dfs.emplace(false, adjacent);
                }
            }
        }
    }

    std::unordered_map<int, int> positions;
    int index = 0;

    std::vector<int> t_sort;
    while (!post_order.empty()) {
        int vertex = post_order.top();
        t_sort.push_back(vertex);

        positions[vertex] = index++;

        post_order.pop();
    }

    for (int v = 1; v <= n; ++v) {
        for (const auto& u : vertices[v]) {
            if (positions[v] > positions[u]) {
                std::cout << "There is a cycle!\n";
                return;
            }
        }
    }

    if (n <= 200) {
        for (const auto& v : t_sort) {
            std::cout << v << std::endl;
        }
    }
}



void Graph::SCCs() {
	resetVisitedVertices();

    std::stack<std::pair<bool, int>> dfs;
    std::stack<int> stack;

    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) {
            dfs.push(std::make_pair(false, v));
        }

        while (!dfs.empty()) {
            std::pair<bool, int> node = dfs.top();
            dfs.pop();

            if (node.first) {
                stack.push(node.second);
                continue;
            }

            if (visited[node.second]) {
                continue;
            }

            visited[node.second] = true;
            dfs.push(std::make_pair(true, node.second));
            const auto& new_vec = vertices[node.second];
            for (const auto son : new_vec) {
                if (!visited[son]) {
                    dfs.push(std::make_pair(false, son));
                }
            }
        }
    }

	Graph g = getTranspose(*this);

	resetVisitedVertices();

    std::vector<int> sizes;
	while (!stack.empty()) {
		int v = stack.top();
		stack.pop();

		if (!visited[v]) {
            g.scc_size = 0;
			g.DFSUtil(v, visited);
            sizes.push_back(g.scc_size);
            ++scc_amt;
			if (n <= 200) std::cout << std::endl;
		}
	}

    std::cout << "There are " << scc_amt << " strongly connected components.\n";
    scc_amt = 0;

    std::cout << "There are following number of elements in each SCC:\n";
    for (const auto& v : sizes) {
        std::cout << v << std::endl;
    }
}

void Graph::DFSUtil(int v, std::vector<bool>& visited) {
    visited[v] = true;
    if (n <= 200) std::cout << v << " ";
    ++scc_size;

    std::stack<std::pair<bool, int>> dfs;

    for (const auto& u : vertices[v]) {
        if (!visited[u]) {
            dfs.push(std::make_pair(false, u));
        }

        while (!dfs.empty()) {
            std::pair<bool, int> node = dfs.top();
            dfs.pop();

            if (visited[node.second]) {
                continue;
            }

            visited[node.second] = true;

            if (n <= 200) std::cout << node.second << " ";
            ++scc_size;

            dfs.push(std::make_pair(true, node.second));
            const auto& new_vec = vertices[node.second];
            for (const auto son : new_vec) {
                if (!visited[son]) {
                    dfs.push(std::make_pair(false, son));
                }
            }
        }
    }
}

bool Graph::isBipartite() {
	std::vector<int> color(n + 1, -1);

	std::queue<std::pair<int, int>> queue;

	std::vector<int> v1, v2;

	for (const auto& v : std::views::iota(1, n + 1)) {
		if (color[v] == -1) {
			queue.push({ v, 0 });
			color[v] = 0;
			v1.push_back(v);

			while (!queue.empty()) {
				std::pair<int, int> p = queue.front();
				queue.pop();

				int u = p.first;
				int w = p.second;

				for (int j : vertices[u]) {
					if (color[j] == w) {
						return false;
					}

					if (color[j] == -1) {
						if (w) {
							color[j] = 0;
							v1.push_back(j);
						} else {
							color[j] = 1;
							v2.push_back(j);
						}

						queue.push({ j, color[j] });
					}
				}
			}
		}
	}

	if (n <= 200) {
		std::cout << "V1:\n";
		for (const auto& v : v1) {
			std::cout << v << " ";
		}

		std::cout << std::endl << std::endl;

		std::cout << "V2:\n";
		for (const auto& v : v2) {
			std::cout << v << " ";
		}

		std::cout << std::endl << std::endl;
	}

	return true;
}

Graph Graph::getTranspose(const Graph& other) {
	Graph g = *this;
	g.vertices.clear();
	
	for (const auto& v : std::views::iota(1, g.n + 1)) {
		for (const auto& u : vertices[v]) {
			g.vertices[u].push_back(v);
		}
	}

	return g;
}