package com.example.minesweeper;

import java.util.ArrayList;
import java.util.List;

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

    public List<Cell> getCells() { return grid; }
}
