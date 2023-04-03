package com.example.minesweeper

class GameController(size: Int, numberOfBombs: Int) {
    val grid: Grid
    private var clearMode = true
    var isFlagMode = false
        private set
    var isGameOver = false
        private set
    var flagCount = 0
        private set
    val numberOfBombs: Int

    init {
        grid = Grid(size)
        grid.generateGrid(numberOfBombs)
        this.numberOfBombs = numberOfBombs
    }

    fun handleCellClick(cell: Cell) {
        if (!isGameOver) {
            if (clearMode) {
                clear(cell)
            } else {
                flag(cell)
            }
        }
    }

    fun clear(cell: Cell) {
        val index = grid.cells.indexOf(cell)
        grid.cells[index].isRevealed = true
        if (cell.value == Cell.BLANK) {
            val toClear: MutableList<Cell> = ArrayList()
            val toCheckAdjacents: MutableList<Cell> = ArrayList()
            toCheckAdjacents.add(cell)
            while (toCheckAdjacents.size > 0) {
                val c = toCheckAdjacents[0]
                val cellIndex = grid.cells.indexOf(c)
                val cellPos = grid.toXY(cellIndex)
                for (adjacent in grid.getAdjacentCells(cellPos[0], cellPos[1])) {
                    if (adjacent.value == Cell.BLANK) {
                        if (!toClear.contains(adjacent)) {
                            if (!toCheckAdjacents.contains(adjacent)) {
                                toCheckAdjacents.add(adjacent)
                            }
                        }
                    } else {
                        if (!toClear.contains(adjacent)) {
                            toClear.add(adjacent)
                        }
                    }
                }
                toCheckAdjacents.remove(c)
                toClear.add(c)
            }
            for (c in toClear) {
                c.isRevealed = true
            }
        } else if (cell.value == Cell.BOMB) {
            isGameOver = true
        }
    }

    val isGameWon: Boolean
        get() {
            var bombsFlagged = 0
            for (c in grid.cells) {
                if (c.value != Cell.BOMB && c.value != Cell.BLANK && !c.isRevealed) {
                    return false
                } else if (c.value == Cell.BOMB && !c.isFlagged) {
                    return false
                } else if (c.value == Cell.BOMB && c.isFlagged) {
                    bombsFlagged++
                }
            }
            return bombsFlagged == numberOfBombs
        }

    fun toggleMode() {
        clearMode = !clearMode
        isFlagMode = !isFlagMode
    }

    fun flag(cell: Cell) {
        if (!cell.isRevealed) {
            cell.isFlagged = !cell.isFlagged
            var count = 0
            for (c in grid.cells) {
                if (c.isFlagged) {
                    count++
                }
            }
            flagCount = count
        }
    }
}