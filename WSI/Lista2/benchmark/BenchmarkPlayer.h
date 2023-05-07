#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <utility>

#include "board.h"

#define WIN_VALUE 1000
#define LOSE_VALUE -1000

const int nearWin[28][3][2] = { 
  { {0,0}, {0,1}, {0,3} },
  { {1,0}, {1,1}, {1,3} },
  { {2,0}, {2,1}, {2,3} },
  { {3,0}, {3,1}, {3,3} },
  { {4,0}, {4,1}, {4,3} },
  { {0,1}, {0,2}, {0,4} },
  { {1,1}, {1,2}, {1,4} },
  { {2,1}, {2,2}, {2,4} },
  { {3,1}, {3,2}, {3,4} },
  { {4,1}, {4,2}, {4,4} },
  { {0,0}, {1,0}, {3,0} },
  { {0,1}, {1,1}, {3,1} },
  { {0,2}, {1,2}, {3,2} },
  { {0,3}, {1,3}, {3,3} },
  { {0,4}, {1,4}, {3,4} },
  { {1,0}, {2,0}, {4,0} },
  { {1,1}, {2,1}, {4,1} },
  { {1,2}, {2,2}, {4,2} },
  { {1,3}, {2,3}, {4,3} },
  { {1,4}, {2,4}, {4,4} },
  { {0,1}, {1,2}, {3,4} },
  { {0,0}, {1,1}, {3,3} },
  { {1,1}, {2,2}, {4,4} },
  { {1,0}, {2,1}, {4,3} },
  { {0,3}, {1,2}, {3,0} },
  { {0,4}, {1,3}, {3,1} },
  { {1,3}, {2,2}, {4,0} },
  { {1,4}, {2,3}, {4,1} }
};

inline bool nearWinBlockCheck(int** board, int player) {
  for(int i=0; i<28; i++)
    if( (board[win[i][0][0]][win[i][0][1]]==player) && (board[win[i][1][0]][win[i][1][1]]==player) && (board[win[i][2][0]][win[i][2][1]]==3 - player) && (board[win[i][3][0]][win[i][3][1]]==player) )
      return true;

  return false;
}

struct BenchmarkResult {
	uint64_t win_count;
	uint16_t depth;
	uint16_t player_no;
	uint16_t player_win_modifier;
	uint16_t player_lose_modifier;
	uint16_t opponent_win_modifier;
	uint16_t opponent_lose_modifier;
	uint16_t player_near_win_block_modifier;
	uint16_t opponent_near_win_block_modifier;
};

struct CompareBenchmarkResults {
	bool operator()(const BenchmarkResult& first, const BenchmarkResult& second) {
		return first.win_count <= second.win_count;
	}
};

class BenchmarkPlayer {
public:
	BenchmarkPlayer(
		int depth,
		int player_no,
		int player_win_modifier,
		int player_lose_modifier,
		int opponent_win_modifier,
		int opponent_lose_modifier,
		int player_near_win_block_modifier,
		int opponent_near_win_block_modifier,
		int** board)
	: depth(depth),
	currentPlayer(player_no),
	player_win_modifier(player_win_modifier),
	player_lose_modifier(player_lose_modifier),
	opponent_win_modifier(opponent_win_modifier),
	opponent_lose_modifier(opponent_lose_modifier),
	player_near_win_block_modifier(player_near_win_block_modifier),
	opponent_near_win_block_modifier(opponent_near_win_block_modifier),
	board(board) {}

	int evaluateBoard(int player) {
	  if (winCheck(board, player))
	      return WIN_VALUE * player_win_modifier;
	  else if (loseCheck(board, player))
	      return LOSE_VALUE * player_lose_modifier;
	  else if (winCheck(board, 3 - player))
	      return LOSE_VALUE * opponent_win_modifier;
	  else if (loseCheck(board, 3 - player))
	      return WIN_VALUE * opponent_lose_modifier;
	  else if (nearWinBlockCheck(board, player))
	      return LOSE_VALUE * player_near_win_block_modifier;
	  else if (nearWinBlockCheck(board, 3 - player))
	      return WIN_VALUE * opponent_near_win_block_modifier;
	  
	  return 0;
	}

	int minmax(int depth, int player, int alpha, int beta) {
	  if (depth == 0 || winCheck(board, 1) || winCheck(board, 2) || loseCheck(board, 1) || loseCheck(board, 2) || nearWinBlockCheck(board, 1) || nearWinBlockCheck(board, 2))
	    return evaluateBoard(player);

	  int winLoseStats = 0;
	  int bestValue = INT_MIN;
	  for (int i = 0; i < 5; i++) {
	    for (int j = 0; j < 5; j++) {
	      if (board[i][j] == 0) {
	        board[i][j] = player;
	        int value = minmax(depth - 1, 3 - player, alpha, beta);
	        board[i][j] = 0;

	        winLoseStats = 0;
	        if (player != currentPlayer) {
	          winLoseStats += value;

	          bestValue = std::max(bestValue, winLoseStats);
	          alpha = std::max(alpha, bestValue);
	          if (beta <= alpha)
	            return bestValue;
	        } else {
	          winLoseStats -= value;

	          bestValue = std::max(bestValue, winLoseStats);
	          beta = std::min(beta, bestValue);
	          if (beta <= alpha)
	            return bestValue;
	        }
	      }
	    }
	  }
	  return bestValue;
	}

	std::pair<int, int> findBestMove() {
	    int bestValue = INT_MIN;
	    std::pair<int, int> bestMove;

	    for (int i = 0; i < 5; i++) {
	        for (int j = 0; j < 5; j++) {
	            if (board[i][j] == 0) {
	                board[i][j] = currentPlayer;
	                int moveValue = minmax(depth - 1, currentPlayer, INT_MIN, INT_MAX);
	                board[i][j] = 0;

	                if (moveValue > bestValue) {
	                    bestValue = moveValue;
	                    bestMove = std::make_pair(i + 1, j + 1);
	                }
	            }
	        }
	    }

	    return bestMove;
	}

	uint16_t depth = 0;
	uint16_t currentPlayer = 0;

	uint16_t player_win_modifier = 0;
	uint16_t player_lose_modifier = 0;
	uint16_t opponent_win_modifier = 0;
	uint16_t opponent_lose_modifier = 0;
	uint16_t player_near_win_block_modifier = 0;
	uint16_t opponent_near_win_block_modifier = 0;
	
	int** board;
};