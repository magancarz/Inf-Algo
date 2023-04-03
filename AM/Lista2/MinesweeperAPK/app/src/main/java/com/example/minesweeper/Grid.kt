package com.example.minesweeper

import java.util.*

class Grid(private val size: Int) {
    private val grid: MutableList<Cell> = ArrayList()

    init {
        initializeGrid()
    }

    private fun initializeGrid() {
        for (i in 0 until size * size) {
            grid.add(Cell(Cell.BLANK))
        }
    }

    fun generateGrid(numberOfBombs: Int) {
        var bombsPlaced = 0
        while (bombsPlaced < numberOfBombs) {
            val x = Random().nextInt(size)
            val y = Random().nextInt(size)
            val index = toIndex(x, y)
            if (grid[index].value == Cell.BLANK) {
                grid[index] = Cell(Cell.BOMB)
                bombsPlaced++
            }
        }
        for (x in 0 until size) {
            for (y in 0 until size) {
                if (getCellAt(x, y)!!.value != Cell.BOMB) {
                    val adjacentCells = getAdjacentCells(x, y)
                    var countBombs = 0
                    for (adjacentCell in adjacentCells) {
                        if (adjacentCell.value == Cell.BOMB) {
                            countBombs++
                        }
                    }
                    if (countBombs > 0) {
                        grid[toIndex(x, y)] = Cell(countBombs)
                    }
                }
            }
        }
    }

    fun getAdjacentCells(x: Int, y: Int): List<Cell> {
        val adjacentCells: MutableList<Cell> = ArrayList()
        val temporaryCellList: MutableList<Cell?> = ArrayList()
        temporaryCellList.add(getCellAt(x - 1, y - 1))
        temporaryCellList.add(getCellAt(x, y - 1))
        temporaryCellList.add(getCellAt(x + 1, y - 1))
        temporaryCellList.add(getCellAt(x + 1, y))
        temporaryCellList.add(getCellAt(x + 1, y + 1))
        temporaryCellList.add(getCellAt(x, y + 1))
        temporaryCellList.add(getCellAt(x - 1, y + 1))
        temporaryCellList.add(getCellAt(x - 1, y))
        for (cell in temporaryCellList) {
            if (cell != null) {
                adjacentCells.add(cell)
            }
        }
        return adjacentCells
    }

    fun revealAllBombs() {
        for (cell in cells) {
            if (cell.value == Cell.BOMB) {
                cell.isRevealed = true
            }
        }
    }

    private fun getCellAt(x: Int, y: Int): Cell? {
        return if (x < 0 || x >= size || y < 0 || y >= size) {
            null
        } else grid[toIndex(x, y)]
    }

    fun toIndex(x: Int, y: Int): Int {
        return x + y * size
    }

    fun toXY(index: Int): IntArray {
        val y = index / size
        val x = index - y * size
        return intArrayOf(x, y)
    }

    val cells: List<Cell>
        get() = grid
}