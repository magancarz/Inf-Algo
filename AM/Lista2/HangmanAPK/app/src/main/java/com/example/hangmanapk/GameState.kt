package com.example.hangmanapk

sealed class GameState {
    class Running(val lettersUsed: String,
                  val hiddenWord: String,
                  val drawable: Int) : GameState()
    class Lost(val wordToGuess: String) : GameState()
    class Won(val wordToGuess: String) : GameState()
}
