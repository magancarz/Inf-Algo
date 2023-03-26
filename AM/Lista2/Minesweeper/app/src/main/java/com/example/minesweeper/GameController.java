package com.example.minesweeper;

public class GameController {
    private Grid grid;

    public GameController(int size, int numberOfBombs) {
        grid = new Grid(size);
        grid.generateGrid(numberOfBombs);
    }

    public Grid getGrid() { return grid; }
}
