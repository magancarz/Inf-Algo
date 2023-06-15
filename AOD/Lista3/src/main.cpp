#include <chrono>
#include <iostream>
#include <execution>
#include <fstream>

#include "DijkstraBenchmark.h"
#include "Graph.h"
#include "dijkstraImpl/Dijkstra.h"

#define DEBUG 1

struct BenchmarkInput
{
	std::string benchmark_name;
	std::vector<std::string> graph_inputs;
	std::vector<std::string> sources_inputs;
	std::vector<std::string> paths_inputs;
};

struct SourcesResult
{
	int v;
	int m;
	uint64_t max_weight;
	int64_t time;
	float avg_time;
};

int main()
{
	std::vector<BenchmarkInput> benchmark_inputs;

	/*benchmark_inputs.push_back(BenchmarkInput
	{
		"square-n",
		{
			"benchmarks/inputs/Square-n/Square-n.10.0.gr",
			"benchmarks/inputs/Square-n/Square-n.11.0.gr",
			"benchmarks/inputs/Square-n/Square-n.12.0.gr",
			"benchmarks/inputs/Square-n/Square-n.13.0.gr",
			"benchmarks/inputs/Square-n/Square-n.14.0.gr",
			"benchmarks/inputs/Square-n/Square-n.15.0.gr",
			"benchmarks/inputs/Square-n/Square-n.16.0.gr",
			"benchmarks/inputs/Square-n/Square-n.17.0.gr",
			"benchmarks/inputs/Square-n/Square-n.18.0.gr",
			"benchmarks/inputs/Square-n/Square-n.19.0.gr",
			"benchmarks/inputs/Square-n/Square-n.20.0.gr",
			"benchmarks/inputs/Square-n/Square-n.21.0.gr"
		},
		{
			"benchmarks/inputs/Square-n/Square-n.10.0.ss",
			"benchmarks/inputs/Square-n/Square-n.11.0.ss",
			"benchmarks/inputs/Square-n/Square-n.12.0.ss",
			"benchmarks/inputs/Square-n/Square-n.13.0.ss",
			"benchmarks/inputs/Square-n/Square-n.14.0.ss",
			"benchmarks/inputs/Square-n/Square-n.15.0.ss",
			"benchmarks/inputs/Square-n/Square-n.16.0.ss",
			"benchmarks/inputs/Square-n/Square-n.17.0.ss",
			"benchmarks/inputs/Square-n/Square-n.18.0.ss",
			"benchmarks/inputs/Square-n/Square-n.19.0.ss",
			"benchmarks/inputs/Square-n/Square-n.20.0.ss",
			"benchmarks/inputs/Square-n/Square-n.21.0.ss"
		},
		{
			"benchmarks/inputs/Square-n/Square-n.10.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.11.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.12.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.13.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.14.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.15.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.16.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.17.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.18.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.19.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.20.0.p2p",
			"benchmarks/inputs/Square-n/Square-n.21.0.p2p"
		}
	});*/

	benchmark_inputs.push_back(BenchmarkInput
	{
		"square-c",
		{
			"benchmarks/inputs/Square-C/Square-C.5.0.gr",
			"benchmarks/inputs/Square-C/Square-C.6.0.gr",
			"benchmarks/inputs/Square-C/Square-C.7.0.gr",
			"benchmarks/inputs/Square-C/Square-C.8.0.gr",
			"benchmarks/inputs/Square-C/Square-C.9.0.gr",
			"benchmarks/inputs/Square-C/Square-C.10.0.gr",
			"benchmarks/inputs/Square-C/Square-C.11.0.gr",
			"benchmarks/inputs/Square-C/Square-C.12.0.gr",
			"benchmarks/inputs/Square-C/Square-C.13.0.gr",
			"benchmarks/inputs/Square-C/Square-C.14.0.gr",
			"benchmarks/inputs/Square-C/Square-C.15.0.gr"
		},
		{
			"benchmarks/inputs/Square-C/Square-C.5.0.ss",
			"benchmarks/inputs/Square-C/Square-C.6.0.ss",
			"benchmarks/inputs/Square-C/Square-C.7.0.ss",
			"benchmarks/inputs/Square-C/Square-C.8.0.ss",
			"benchmarks/inputs/Square-C/Square-C.9.0.ss",
			"benchmarks/inputs/Square-C/Square-C.10.0.ss",
			"benchmarks/inputs/Square-C/Square-C.11.0.ss",
			"benchmarks/inputs/Square-C/Square-C.12.0.ss",
			"benchmarks/inputs/Square-C/Square-C.13.0.ss",
			"benchmarks/inputs/Square-C/Square-C.14.0.ss",
			"benchmarks/inputs/Square-C/Square-C.15.0.ss"
		},
		{
			"benchmarks/inputs/Square-C/Square-C.5.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.6.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.7.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.8.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.9.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.10.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.11.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.12.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.13.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.14.0.p2p",
			"benchmarks/inputs/Square-C/Square-C.15.0.p2p"
		}
	});

	/*benchmark_inputs.push_back(BenchmarkInput
	{
		"random4-n",
		{
			"benchmarks/inputs/Random4-n/Random4-n.10.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.11.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.12.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.13.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.14.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.15.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.16.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.17.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.18.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.19.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.20.0.gr",
			"benchmarks/inputs/Random4-n/Random4-n.21.0.gr"
		},
		{
			"benchmarks/inputs/Random4-n/Random4-n.10.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.11.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.12.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.13.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.14.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.15.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.16.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.17.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.18.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.19.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.20.0.ss",
			"benchmarks/inputs/Random4-n/Random4-n.21.0.ss"
		},
		{
			"benchmarks/inputs/Random4-n/Random4-n.10.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.11.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.12.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.13.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.14.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.15.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.16.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.17.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.18.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.19.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.20.0.p2p",
			"benchmarks/inputs/Random4-n/Random4-n.21.0.p2p"
		}
	});*/

	/*benchmark_inputs.push_back(BenchmarkInput
	{
		"usa-road-d",
		{
			"benchmarks/inputs/USA-road-d/USA-road-d.NY.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.BAY.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.COL.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.FLA.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.NW.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.NE.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.CAL.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.LKS.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.E.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.W.gr",
			"benchmarks/inputs/USA-road-d/USA-road-d.CTR.gr",
		},
		{
			"benchmarks/inputs/USA-road-d/USA-road-d.NY.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.BAY.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.COL.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.FLA.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.NW.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.NE.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.CAL.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.LKS.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.E.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.W.ss",
			"benchmarks/inputs/USA-road-d/USA-road-d.CTR.ss",
		},
		{
			"benchmarks/inputs/USA-road-d/USA-road-d.NY.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.BAY.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.COL.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.FLA.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.NW.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.NE.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.CAL.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.LKS.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.E.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.W.p2p",
			"benchmarks/inputs/USA-road-d/USA-road-d.CTR.p2p",
		}
	});*/

	std::for_each(benchmark_inputs.begin(), benchmark_inputs.end(), [&] (const auto& path_input)
	{
		std::vector<SourcesResult> dijkstra_results;
		std::vector<SourcesResult> dial_results;
		std::vector<SourcesResult> radix_results;

		std::ofstream results_file(path_input.benchmark_name + "-paths-benchmark-results.txt");
		for (int i = 0; i < path_input.graph_inputs.size(); ++i)
		{
			std::cout << "Running on " << path_input.graph_inputs[i] << std::endl;
			auto dijkstra_benchmark = aod::DijkstraBenchmark(
				path_input.graph_inputs[i],
				path_input.sources_inputs[i],
				path_input.paths_inputs[i]);

			auto start = std::chrono::steady_clock::now();

			auto dijkstra_result = dijkstra_benchmark.normalDijkstraPathsBenchmark();

			auto end = std::chrono::steady_clock::now();
		#if DEBUG 1
			std::cout << "(Dijkstra) time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds."
				<< std::endl;
		#endif
			dijkstra_results.push_back(
				SourcesResult
				{
					dijkstra_benchmark.graph.v,
					dijkstra_benchmark.graph.m,
					aod::findMaxWeightInGraph(dijkstra_benchmark.graph),
					std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(),
					static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / dijkstra_benchmark.benchmark_pairs.path_goals.size()
				});

			start = std::chrono::steady_clock::now();

			auto dial_dijkstra_result = dijkstra_benchmark.dialDijkstraPathsBenchmark();

			end = std::chrono::steady_clock::now();
		#if DEBUG 1
			std::cout << "(Dijkstra Dial) time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds."
				<< std::endl;
		#endif
			dial_results.push_back(
				SourcesResult
				{
					dijkstra_benchmark.graph.v,
					dijkstra_benchmark.graph.m,
					aod::findMaxWeightInGraph(dijkstra_benchmark.graph),
					std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(),
					static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / dijkstra_benchmark.benchmark_pairs.path_goals.size()
				});

			start = std::chrono::steady_clock::now();

			auto radix_dijkstra_result = dijkstra_benchmark.radixHeapDijkstraPathsBenchmark();

			end = std::chrono::steady_clock::now();
		#if DEBUG 1
			std::cout << "(Dijkstra Radix Heap) time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds."
				<< std::endl;
		#endif
			radix_results.push_back(
				SourcesResult
				{
					dijkstra_benchmark.graph.v,
					dijkstra_benchmark.graph.m,
					aod::findMaxWeightInGraph(dijkstra_benchmark.graph),
					std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(),
					static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / dijkstra_benchmark.benchmark_pairs.path_goals.size()
				});

			if (results_file.is_open())
			{
				results_file
				<< dijkstra_results[i].v << " & "
				<< dijkstra_results[i].m << " & "
				<< dijkstra_results[i].max_weight << " & "
				<< dijkstra_results[i].time << " & "
				<< dijkstra_results[i].avg_time << " & "
				<< dial_results[i].time << " & "
				<< dial_results[i].avg_time << " & "
				<< radix_results[i].time << " & "
				<< radix_results[i].avg_time
				<< " \\\\"
				<< " \\hline" << std::endl;
			}
		}
	});
}