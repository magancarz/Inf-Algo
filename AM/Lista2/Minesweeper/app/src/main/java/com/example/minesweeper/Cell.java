package com.example.minesweeper;

public class Cell {
    public static final int BOMB = -1;
    public static final int BLANK = 0;

    private int value;
    private boolean isRevealed = false;
    private boolean isFlagged = false;

    public Cell(int value) {
        this.value = value;
    }

    public int getValue() { return value; }
    public void setValue(int value) { this.value = value; }
    public boolean isRevealed() { return isRevealed; }
    public void setRevealed(boolean isRevealed) { this.isRevealed = isRevealed; }
    public boolean isFlagged() { return isFlagged; }
    public void setFlagged(boolean isFlagged) { this.isFlagged = isFlagged; }
}