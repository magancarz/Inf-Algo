#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>

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

			edges.push_back(std::pair<int, int>(std::stoi(u), std::stoi(v)));
		}

		file_stream.close();
	} else {
		std::cout << "Unable to open file!\n";
	}
}
