#include "Graph.h"

#include <fstream>
#include <sstream>

namespace aod {

	Graph loadGraphFromFile(const std::string& filename) {

		std::ifstream file_stream(filename);
		if (file_stream.is_open()) {

			Graph graph{};

			std::string line;
			while (getline(file_stream, line)) {

				if (line[0] == 'p') {

					std::stringstream iss(line);
					std::string p, sp, n, m;
					iss >> p;
					iss >> sp;
					iss >> n;
					iss >> m;

					graph.v = std::stoi(n);
					graph.m = std::stoi(m);
				} else if (line[0] == 'a') {

					std::stringstream iss(line);
					std::string a, from, to, cost;
					iss >> a;
					iss >> from;
					iss >> to;
					iss >> cost;

					graph.adjacency_list[std::stoi(from)].push_back({ std::stoi(to), std::stoi(cost) });
				}

				if (line[0] == 'c') {
					//ignore
				}
			}

			file_stream.close();

			return graph;
		}

		throw std::runtime_error("Error: unable to open graph file!");
	}
}