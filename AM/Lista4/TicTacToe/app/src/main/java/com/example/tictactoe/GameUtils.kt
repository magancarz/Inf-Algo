package com.example.tictactoe

import java.util.*
import kotlin.collections.ArrayList

object GameUtils {
    const val PLAYER_X = "X"
    const val PLAYER_O = "O"

    fun isBoardFull(board: ArrayList<String>): Boolean {
        for (i in board) {
            if (i != PLAYER_X && i != PLAYER_O) return false
        }
        return true
    }

    fun isGameWon(board: ArrayList<String>, player: String, size: Int): Boolean {
        for (y in 0 until size) {
            for (x in 0 until size) {
                if (board[y * size + x] == player) {
                    if (x <= size - 3 && board[y * size + x + 1] == player && board[y * size + x + 2] == player) return true
                    if (y <= size - 3 && board[(y + 1) * size + x] == player && board[(y + 2) * size + x] == player) return true
                    if (x <= size - 3 && y <= size - 3 && board[(y + 1) * size + x + 1] == player && board[(y + 2) * size + x + 2] == player) return true
                    if (x <= size - 3 && y >= 2 && board[(y - 1) * size + x + 1] == player && board[(y - 2) * size + x + 2] == player) return true
                }
            }
        }

        return false
    }

    fun gameResult(board: ArrayList<String>, size: Int): String {
        when {
            isGameWon(board, PLAYER_X, size) -> return "${"PLAYER X"} Won"
            isGameWon(board, PLAYER_O, size) -> return "${"PLAYER O"} Won"
            isBoardFull(board) -> return "It is Tie"
        }
        return "Tie"
    }
}