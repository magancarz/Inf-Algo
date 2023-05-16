#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <iostream>
#include <limits.h>
#include <utility>

#include "board.h"

#define WIN_VALUE 1000
#define LOSE_VALUE -1000

const int nearWin[28][3][2] = { 
  { {0,0}, {0,1},{0,3} },
  { {1,0}, {1,1},{1,3} },
  { {2,0}, {2,1},{2,3} },
  { {3,0}, {3,1},{3,3} },
  { {4,0}, {4,1},{4,3} },
  { {0,1}, {0,2},{0,4} },
  { {1,1}, {1,2},{1,4} },
  { {2,1}, {2,2},{2,4} },
  { {3,1}, {3,2},{3,4} },
  { {4,1}, {4,2},{4,4} },
  { {0,0}, {1,0},{3,0} },
  { {0,1}, {1,1},{3,1} },
  { {0,2}, {1,2},{3,2} },
  { {0,3}, {1,3},{3,3} },
  { {0,4}, {1,4},{3,4} },
  { {1,0}, {2,0},{4,0} },
  { {1,1}, {2,1},{4,1} },
  { {1,2}, {2,2},{4,2} },
  { {1,3}, {2,3},{4,3} },
  { {1,4}, {2,4},{4,4} },
  { {0,1}, {1,2},{3,4} },
  { {0,0}, {1,1},{3,3} },
  { {1,1}, {2,2},{4,4} },
  { {1,0}, {2,1},{4,3} },
  { {0,3}, {1,2},{3,0} },
  { {0,4}, {1,3},{3,1} },
  { {1,3}, {2,2},{4,0} },
  { {1,4}, {2,3},{4,1} }
};

bool nearWinBlockCheck(int player) {
  for(int i=0; i<28; i++)
    if( (board[win[i][0][0]][win[i][0][1]]==player) && (board[win[i][1][0]][win[i][1][1]]==player) && (board[win[i][2][0]][win[i][2][1]]==3 - player) && (board[win[i][3][0]][win[i][3][1]]==player) )
      return true;

  return false;
}

int bestMove = -1;

int depth = 0;
int currentPlayer = 0;

int evaluateBoard(int player) {
  if (winCheck(player))
      return WIN_VALUE * 10000;
  else if (loseCheck(player))
      return LOSE_VALUE * 10000;
  else if (winCheck(3 - player))
      return LOSE_VALUE * 100;
  else if (loseCheck(3 - player))
      return WIN_VALUE * 100;
  else if (nearWinBlockCheck(player))
      return LOSE_VALUE * 100;
  else if (nearWinBlockCheck(3 - player))
      return WIN_VALUE * 100000;
  
  return 0;
}

int minmax(int depth, int player, int alpha, int beta) {
  if (depth == 0 || winCheck(1) || winCheck(2) || loseCheck(1) || loseCheck(2))
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

int main(int argc, char *argv[]) {
  int socket_desc;
  struct sockaddr_in server_addr;
  char server_message[16], client_message[16];

  bool end_game;
  int player, msg, move;

  if( argc!=5 ) {
    printf("Wrong number of arguments\n");
    return -1;
  }

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if( socket_desc<0 ) {
    printf("Unable to create socket\n");
    return -1;
  }
  printf("Socket created successfully\n");

  // Set port and IP the same as server-side
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // Send connection request to server
  if( connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0 ) {
    printf("Unable to connect\n");
    return -1;
  }
  printf("Connected with server successfully\n");

  // Receive the server message
  memset(server_message, '\0', sizeof(server_message));
  if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
    printf("Error while receiving server's message\n");
    return -1;
  }
  printf("Server message: %s\n",server_message);

  memset(client_message, '\0', sizeof(client_message));
  strcpy(client_message, argv[3]);
  // Send the message to server
  if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
    printf("Unable to send message\n");
    return -1;
  }

  setBoard(); 
  end_game = false;
  player = atoi(argv[3]);
  depth = atoi(argv[4]);
  currentPlayer = player;

  while( !end_game ) {
    memset(server_message, '\0', sizeof(server_message));
    if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
      printf("Error while receiving server's message\n");
      return -1;
    }
    printf("Server message: %s\n", server_message);
    msg = atoi(server_message);
    move = msg%100;
    msg = msg/100;
    if( move!=0 ) {
      setMove(move, 3-player);
      printBoard();
    }
    if( (msg==0) || (msg==6) ) {
      std::pair<int, int> bestMoveResult = findBestMove();
      bestMove = (bestMoveResult.first) * 10 + bestMoveResult.second;

      setMove(bestMove, player);
      printBoard();
      memset(client_message, '\0', sizeof(client_message));
      sprintf(client_message, "%d", bestMove);
      if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
        printf("Unable to send message\n");
        return -1;
      }
      printf("Client message: %s\n", client_message);
    }
    else {
      end_game = true;
      switch( msg ) {
        case 1 : printf("You won.\n"); break;
        case 2 : printf("You lost.\n"); break;
        case 3 : printf("Draw.\n"); break;
        case 4 : printf("You won. Opponent error.\n"); break;
        case 5 : printf("You lost. Your error.\n"); break;
      }
    }
  }

  // Close socket
  close(socket_desc);

  return 0;
}
