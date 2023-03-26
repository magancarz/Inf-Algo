package com.example.minesweeper;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Grid {
    private List<Cell> grid = new ArrayList<Cell>();
    private int size;

    public Grid(int size) {
        this.size = size;

        initializeGrid();
    }

    private void initializeGrid() {
        for (int i = 0; i < size * size; i++) {
            grid.add(new Cell(Cell.BLANK));
        }
    }

    public void generateGrid(int numberOfBombs) {
        int bombsPlaced = 0;
        while (bombsPlaced < numberOfBombs) {
            int x = new Random().nextInt(size);
            int y = new Random().nextInt(size);

            int index = toIndex(x, y);
            if (grid.get(index).getValue() == Cell.BLANK) {
                grid.set(index, new Cell(Cell.BOMB));
                bombsPlaced++;
            }
        }

        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                if (getCellAt(x, y).getValue() != Cell.BOMB) {
                    List<Cell> adjacentCells = getAdjacentCells(x, y);
                    int countBombs = 0;
                    for (Cell adjacentCell : adjacentCells) {
                        if (adjacentCell.getValue() == Cell.BOMB) {
                            countBombs++;
                        }
                    }

                    if (countBombs > 0) {
                        grid.set(toIndex(x, y), new Cell(countBombs));
                    }
                }
            }
        }
    }

    public List<Cell> getAdjacentCells(int x, int y) {
        List<Cell> adjacentCells = new ArrayList<Cell>();

        List<Cell> temporaryCellList = new ArrayList<Cell>();
        temporaryCellList.add(getCellAt(x - 1, y - 1));
        temporaryCellList.add(getCellAt(x, y - 1));
        temporaryCellList.add(getCellAt(x + 1, y - 1));
        temporaryCellList.add(getCellAt(x + 1, y));
        temporaryCellList.add(getCellAt(x + 1, y + 1));
        temporaryCellList.add(getCellAt(x, y + 1));
        temporaryCellList.add(getCellAt(x - 1, y + 1));
        temporaryCellList.add(getCellAt(x - 1, y));

        for (Cell cell : temporaryCellList) {
            if (cell != null) {
                adjacentCells.add(cell);
            }
        }

        return adjacentCells;
    }

    private Cell getCellAt(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            return null;
        }

        return grid.get(toIndex(x, y));
    }

    public int toIndex(int x, int y) {
        return x + (y * size);
    }

    public int[] toXY(int index) {
        int y = index / size;
        int x = index - (y * size);

        return new int[] { x, y };
    }

    public List<Cell> getCells() { return grid; }
}
