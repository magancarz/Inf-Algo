package com.example.hangman

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.core.content.ContextCompat
import androidx.core.view.children

class MainActivity : AppCompatActivity() {

    private val gameManager = GameManager()

    private lateinit var wordTextView: TextView
    private lateinit var lettersUsedTextView: TextView
    private lateinit var imageView: ImageView
    private lateinit var newGameButton: Button
    private lateinit var lettersLayout: ConstraintLayout

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        imageView = findViewById(R.id.imageView)
        wordTextView = findViewById(R.id.wordTextView)
        lettersUsedTextView = findViewById(R.id.lettersUsedTextView)
        newGameButton = findViewById(R.id.newGameButton)
        lettersLayout = findViewById(R.id.lettersLayout)

        newGameButton.setOnClickListener {
            startNewGame()
        }

        val gameState = gameManager.startNewGame(this)
        updateUI(gameState)

        lettersLayout.children.forEach { letterView ->
            if (letterView is TextView) {
                letterView.setOnClickListener {
                    val gameState = gameManager.play((letterView).text[0])
                    updateUI(gameState)
                }
            }
        }
    }

    private fun updateUI(gameState: GameState) {
        when (gameState) {
            is GameState.Lost -> gameOver(gameState.wordToGuess)
            is GameState.Running -> {
                wordTextView.text = gameState.hiddenWord
                lettersUsedTextView.text = "Letters used: ${gameState.lettersUsed}"
                imageView.setImageDrawable(ContextCompat.getDrawable(this, gameState.drawable))
            }
            is GameState.Won -> gameWon(gameState.wordToGuess)
        }
    }

    private fun gameOver(wordToGuess: String) {
        Toast.makeText(applicationContext, "Game Lost!", Toast.LENGTH_SHORT).show()
        wordTextView.text = wordToGuess
        imageView.setImageDrawable(ContextCompat.getDrawable(this, R.drawable.wisielec7))
    }

    private fun gameWon(wordToGuess: String) {
        Toast.makeText(applicationContext, "Game Won!", Toast.LENGTH_SHORT).show()
        wordTextView.text = wordToGuess
    }

    private fun startNewGame() {
        val gameState = gameManager.startNewGame(this)
        lettersLayout.visibility = View.VISIBLE
        lettersLayout.children.forEach { letterView ->
            letterView.visibility = View.VISIBLE
        }
        updateUI(gameState)
    }
}