package com.example.tictactoe

import android.util.Log
import android.widget.Toast
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import com.example.tictactoe.GameUtils
import com.example.tictactoe.GameUtils.PLAYER_O
import com.example.tictactoe.GameUtils.PLAYER_X
import com.example.tictactoe.GameUtils.isBoardFull
import com.example.tictactoe.GameUtils.isGameWon

class MainViewModel : ViewModel() {

    var isGameOver = false
    var beforeGame = true
    var winner = ""
    var boardSize = 0
    var board by mutableStateOf(arrayListOf("", "", "", "", "", "", "", "", ""))
        private set

    var currentPlayer = PLAYER_X

    fun startGame(size: String) {
        boardSize = size.split("x")[0].toInt()
        board = ArrayList()
        for (i in 0 until boardSize * boardSize) {
            board.add("")
        }
        beforeGame = false
    }

    fun play(move: Int) {
        if (isGameOver || beforeGame) return

        if (board[move] == "") {
            if (currentPlayer == PLAYER_X) {
                board = ArrayList(board.toMutableList().also {
                    it[move] = PLAYER_X
                })
                currentPlayer = PLAYER_O
            } else {
                board = ArrayList(board.toMutableList().also {
                    it[move] = PLAYER_O
                })
                currentPlayer = PLAYER_X
            }
        }

        isGameOver = isGameWon(board, PLAYER_X, boardSize) || isGameWon(board, PLAYER_O, boardSize) || isBoardFull(board)
        winner = GameUtils.gameResult(board, boardSize)

        Log.d(TAG, "$board")
    }

    fun reset() {
        isGameOver = false
        beforeGame = true
        board  = arrayListOf("", "", "", "", "", "", "", "", "")
        boardSize = 3
    }

    companion object {
        const val TAG = "MainViewModel"
    }
}