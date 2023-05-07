#include "MinimaxBenchmark.h"

#include <chrono>
#include <functional>
#include <queue>

#include "BenchmarkPlayer.h"

#include <vector>

void MinimaxBenchmark::benchmark() {
	std::priority_queue<BenchmarkResult, std::vector<BenchmarkResult>, CompareBenchmarkResults> benchmark_results;

	int max_win_count = 0;

	const auto values = {1, 10, 100};//, 1000, 10000};
	const int count_of_steps = 3;

	std::unordered_map<uint8_t, std::unordered_map<uint8_t, uint8_t>> results;
	int x_step = count_of_steps * count_of_steps;
	int y_step = count_of_steps;
	int z_step = 1;

	int x = 0;
	for (const auto& player_win_modifier : values) {
		int y = 0;
		for (const auto& opponent_win_modifier : values) {
			int z = 0;
			for (const auto& opponent_near_win_block_modifier : values) {
				auto player1 = BenchmarkPlayer(9, 1, player_win_modifier, player_win_modifier, opponent_win_modifier, opponent_win_modifier, player_win_modifier, opponent_near_win_block_modifier, nullptr);
				uint64_t win_count = 0;

				const auto start = std::chrono::steady_clock::now();

				int i = 0;
				for (const auto& second_player_win_modifier : values) {
					int j = 0;
					for (const auto& second_opponent_win_modifier : values) {
						int k = 0;
						for (const auto& second_opponent_near_win_block_modifier : values) {
							if (results[x * x_step + y * y_step + z][i * x_step + j * y_step + k] == 2) {
								++win_count;
							} else if (results[x * x_step + y * y_step + z][i * x_step + j * y_step + k] == 1) {
								continue;
							} else {
								auto player2 = BenchmarkPlayer(9, 2, second_player_win_modifier, second_player_win_modifier, second_opponent_win_modifier, second_opponent_win_modifier, second_player_win_modifier, second_opponent_near_win_block_modifier, nullptr);
								int result = runConfiguration(player1, player2);
								if (result == 1) ++win_count;
								results[i * x_step + j * y_step + k][x * x_step + y * y_step + z] = 3 - result;
							}
							++k;
						}
						++j;
					}
					++i;
				}

				if (win_count > max_win_count) {
					max_win_count = win_count;
					std::cout << "Current winner (" << win_count << " wins):\n" << "depth = " << player1.depth << std::endl
								<< "player_win_modifier = " << player1.player_win_modifier << std::endl
								<< "player_lose_modifier = " << player1.player_lose_modifier << std::endl
								<< "opponent_win_modifier = " << player1.opponent_win_modifier << std::endl
								<< "opponent_lose_modifier = " << player1.opponent_lose_modifier << std::endl
								<< "player_near_win_block_modifier = " << player1.player_near_win_block_modifier << std::endl
								<< "opponent_near_win_block_modifier = " << player1.opponent_near_win_block_modifier << std::endl;
				}

				const auto end = std::chrono::steady_clock::now();
				std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " s." << std::endl;
				benchmark_results.push(BenchmarkResult{
					win_count,
					player1.depth,
					player1.player_win_modifier, player1.player_lose_modifier,
					player1.opponent_win_modifier,
					player1.opponent_lose_modifier,
					player1.player_near_win_block_modifier,
					player1.opponent_near_win_block_modifier});

				++z;
			}
			++y;
		}
		++x;
	}

	std::cout << std::endl;
}

int MinimaxBenchmark::runConfiguration(BenchmarkPlayer& player1, BenchmarkPlayer& player2) {

	//std::cout << "Testing two players configuration:\n";

	int** board = new int*[5];
	for (int i = 0; i < 5; ++i) {
		board[i] = new int[5];
	}
	
	setBoard(board);
	//printBoard(board);

	int no_of_moves = 0;
	int result = 0;

	player1.currentPlayer = 1;
	player1.board = board;
	player2.currentPlayer = 2;
	player2.board = board;

	while (true) {
		auto move = player1.findBestMove();
		auto move_value = move.first * 10 + move.second;
		setMove(board, move_value, player1.currentPlayer);
		++no_of_moves;
		if (no_of_moves >= 25) break;

		//printBoard(board);
		if (no_of_moves >= 7 && winCheck(board, player1.currentPlayer)) {
			//std::cout << "Player 1 won!\n";
			result = 1;
			break;
		}

		if (no_of_moves >= 5 && loseCheck(board, player1.currentPlayer)) {
			//std::cout << "Player 1 lost!\n";
			result = 2;
			break;
		}

		move = player2.findBestMove();
		move_value = move.first * 10 + move.second;
		setMove(board, move_value, player2.currentPlayer);
		++no_of_moves;
		if (no_of_moves >= 25) break;

		//printBoard(board);
		if (no_of_moves >= 7 && winCheck(board, player1.currentPlayer)) {
			//std::cout << "Player 2 won!\n";
			result = 2;
			break;
		}

		if (no_of_moves >= 5 && loseCheck(board, player1.currentPlayer)) {
			//std::cout << "Player 2 lost!\n";
			result = 1;
			break;
		}
	}

	for (int i = 0; i < 5; ++i) {
		delete[] board[i];
	}
	delete[] board;

	return result;
}
