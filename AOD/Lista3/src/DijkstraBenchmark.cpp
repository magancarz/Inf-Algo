#include "DijkstraBenchmark.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <execution>

#include "dijkstra/Dijkstra.h"

namespace aod {

	DijkstraBenchmarkSources loadSourcesFromFile(const std::string& filename) {

		std::ifstream file_stream(filename);
		if (file_stream.is_open()) {

			DijkstraBenchmarkSources benchmark_sources{};

			std::string line;
			while (getline(file_stream, line)) {

				if (line[0] == 'p') {

					std::stringstream iss(line);
					std::string p, aux, sp, ss, no_of_sources;
					iss >> p;
					iss >> aux;
					iss >> sp;
					iss >> ss;
					iss >> no_of_sources;

					for (int i = 0; i < std::stoi(no_of_sources); ++i) {
						getline(file_stream, line);
						std::stringstream iss(line);
						std::string s, source;
						iss >> s;
						iss >> source;
						benchmark_sources.sources.push_back(std::stoi(source));
					}
				}

				if (line[0] == 'c') {
					//ignore
				}
			}

			file_stream.close();

			return benchmark_sources;
		}

		throw std::runtime_error("Error: unable to open sources file!");
	}

	DijkstraBenchmarkPathsGoals loadPathGoalsFromFile(const std::string& filename) {

		std::ifstream file_stream(filename);
		if (file_stream.is_open()) {

			DijkstraBenchmarkPathsGoals benchmark_paths_goals{};

			std::string line;
			while (getline(file_stream, line)) {

				if (line[0] == 'p') {

					std::stringstream iss(line);
					std::string p, aux, sp, p2p, no_of_path_goals;
					iss >> p;
					iss >> aux;
					iss >> sp;
					iss >> p2p;
					iss >> no_of_path_goals;

					for (int i = 0; i < std::stoi(no_of_path_goals); ++i) {
						getline(file_stream, line);

						std::stringstream iss(line);
						std::string from, to;
						iss >> from;
						iss >> to;
						benchmark_paths_goals.path_goals.push_back({ std::stoi(from), std::stoi(to) });
					}
				}

				if (line[0] == 'c') {
					//ignore
				}
			}

			file_stream.close();

			return benchmark_paths_goals;
		}

		throw std::runtime_error("Error: unable to open paths goals file!");
	}

	DijkstraBenchmark::DijkstraBenchmark(aod::Graph& graph, DijkstraBenchmarkSources sources)
		: graph(graph), benchmark_sources(sources) {
		sourcesBenchmark();
	}

	void DijkstraBenchmark::sourcesBenchmark()
	{
		std::for_each(std::execution::par, benchmark_sources.sources.begin(), benchmark_sources.sources.end(),
			[&](int source) 
			{
				const auto start = std::chrono::steady_clock::now();

				aod::dijkstraWithOnlyDistances(graph, source);

				const auto end = std::chrono::steady_clock::now();
				std::cout << "(Dijkstra sources benchmark) source: "
					+ std::to_string(source)
					+ ", time elapsed: "
					<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
					<< " milliseconds." << std::endl;
			});
	}
}