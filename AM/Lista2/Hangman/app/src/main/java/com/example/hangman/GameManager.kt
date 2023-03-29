package com.example.hangman

import android.content.Context
import kotlin.random.Random

class GameManager {

    private var lettersUsed: String = ""
    private lateinit var hiddenWord: String
    private lateinit var wordToGuess: String
    private var maxTries = 7
    private var currentTries = 0
    private var hangmanImage: Int = R.drawable.wisielec0

    fun startNewGame(context: Context) : GameState {
        lettersUsed = ""
        currentTries = 0
        val stringArray = context.resources.getStringArray(R.array.words)
        wordToGuess = stringArray[Random.nextInt(stringArray.size)]
        generateUnderscores(wordToGuess)
        hangmanImage = R.drawable.wisielec0
        return getGameState()
    }

    private fun getGameState(): GameState {
        if (hiddenWord.equals(wordToGuess, true)) {
            return GameState.Won(wordToGuess)
        }

        if (currentTries == maxTries) {
            return GameState.Lost(wordToGuess)
        }

        hangmanImage = getCurrentImageState()
        return GameState.Running(lettersUsed, hiddenWord, hangmanImage)
    }

    fun generateUnderscores(word: String) {
        val stringBuilder = StringBuilder()
        word.forEach { char ->
            stringBuilder.append("_")
        }
        hiddenWord = stringBuilder.toString()
    }

    fun play(letter: Char): GameState {
        if (lettersUsed.contains(letter)) {
            return GameState.Running(lettersUsed, hiddenWord, hangmanImage)
        }

        lettersUsed += letter
        val indexes = mutableListOf<Int>()

        wordToGuess.forEachIndexed { index, char ->
            if (char.equals(letter, true)) {
                indexes.add(index)
            }
        }

        var finalHiddenWord = "" + hiddenWord
        indexes.forEach { index ->
            val stringBuilder = StringBuilder(finalHiddenWord).also { it.setCharAt(index, letter) }
            finalHiddenWord = stringBuilder.toString()
        }

        if (indexes.isEmpty()) {
            currentTries++
        }

        hiddenWord = finalHiddenWord
        return getGameState()
    }

    private fun getCurrentImageState(): Int {
        return when (currentTries) {
            0 -> R.drawable.wisielec0
            1 -> R.drawable.wisielec1
            2 -> R.drawable.wisielec2
            3 -> R.drawable.wisielec3
            4 -> R.drawable.wisielec4
            5 -> R.drawable.wisielec5
            6 -> R.drawable.wisielec6
            7 -> R.drawable.wisielec7
            else -> R.drawable.wisielec7
        }
    }
}