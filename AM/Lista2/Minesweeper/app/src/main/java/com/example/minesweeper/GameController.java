package com.example.minesweeper;

import java.util.ArrayList;
import java.util.List;

public class GameController {
    private Grid grid;
    private boolean clearMode = true;
    private boolean flagMode = false;
    private boolean isGameOver = false;

    private int flagCount = 0;
    private int numberOfBombs;

    public GameController(int size, int numberOfBombs) {
        grid = new Grid(size);
        grid.generateGrid(numberOfBombs);

        this.numberOfBombs = numberOfBombs;
    }

    public void handleCellClick(Cell cell) {
        if (!isGameOver) {
            if (clearMode) {
                clear(cell);
            } else {
                flag(cell);
            }
        }
    }

    public void clear(Cell cell) {
        int index = getGrid().getCells().indexOf(cell);
        getGrid().getCells().get(index).setRevealed(true);

        if (cell.getValue() == Cell.BLANK) {
            List<Cell> toClear = new ArrayList<>();
            List<Cell> toCheckAdjacents = new ArrayList<>();

            toCheckAdjacents.add(cell);

            while (toCheckAdjacents.size() > 0) {
                Cell c = toCheckAdjacents.get(0);
                int cellIndex = getGrid().getCells().indexOf(c);
                int[] cellPos = getGrid().toXY(cellIndex);
                for (Cell adjacent : getGrid().getAdjacentCells(cellPos[0], cellPos[1])) {
                    if (adjacent.getValue() == Cell.BLANK) {
                        if (!toClear.contains(adjacent)) {
                            if (!toCheckAdjacents.contains(adjacent)) {
                                toCheckAdjacents.add(adjacent);
                            }
                        }
                    } else {
                        if (!toClear.contains(adjacent)) {
                            toClear.add(adjacent);
                        }
                    }
                }
                toCheckAdjacents.remove(c);
                toClear.add(c);
            }

            for (Cell c : toClear) {
                c.setRevealed(true);
            }
        } else if (cell.getValue() == Cell.BOMB) {
            isGameOver = true;
        }
    }

    public boolean isGameWon() {
        int bombsFlagged = 0;
        for (Cell c : getGrid().getCells()) {
            if (c.getValue() != Cell.BOMB && c.getValue() != Cell.BLANK && !c.isRevealed()) {
                return false;
            } else if (c.getValue() == Cell.BOMB && !c.isFlagged()) {
                return false;
            } else if (c.getValue() == Cell.BOMB && c.isFlagged()) {
                bombsFlagged++;
            }
        }

        if (bombsFlagged == numberOfBombs) {
            return true;
        }

        return false;
    }

    public void toggleMode() {
        clearMode = !clearMode;
        flagMode = !flagMode;
    }

    public void flag(Cell cell) {
        if (!cell.isRevealed()) {
            cell.setFlagged(!cell.isFlagged());
            int count = 0;
            for (Cell c : getGrid().getCells()) {
                if (c.isFlagged()) {
                    count++;
                }
            }

            flagCount = count;
        }
    }

    public Grid getGrid() { return grid; }

    public boolean isGameOver() { return isGameOver; }

    public boolean isFlagMode() { return flagMode; }

    public int getFlagCount() { return flagCount; }

    public int getNumberOfBombs() { return numberOfBombs; }
}
