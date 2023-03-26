package com.example.minesweeper

class Cell(var value: Int) {
    var isRevealed = false
    var isFlagged = false

    companion object {
        const val BOMB = -1
        const val BLANK = 0
    }
}