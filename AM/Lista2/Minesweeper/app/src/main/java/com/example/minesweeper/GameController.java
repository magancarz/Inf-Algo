package com.example.minesweeper;

public class GameController {
    private Grid grid;

    public GameController(int size) {
        grid = new Grid(size);
    }

    public Grid getGrid() { return grid; }
}
