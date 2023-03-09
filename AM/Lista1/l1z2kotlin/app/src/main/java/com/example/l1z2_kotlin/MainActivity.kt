package com.example.l1z2_kotlin

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.annotation.IntegerRes
import com.google.android.material.textfield.TextInputLayout
import kotlin.random.Random

class MainActivity : AppCompatActivity() {

    private var currentValue = 0
    private var score = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        rollValue()
    }

    private fun rollValue() {
        currentValue = Random.nextInt(100)
    }

    fun checkNumber(view: View) {
        var value = findViewById<EditText>(R.id.textInput).text

        if (value.toString().isEmpty()) return

        try {
            if (currentValue == Integer.parseInt(value.toString())) {
                Toast.makeText(this, "Dobrzeeeee", Toast.LENGTH_SHORT).show()
                score++
                rollValue()
            } else if (currentValue > Integer.parseInt(value.toString())) {
                findViewById<TextView>(R.id.hintText).text = "Podana liczba jest za mała."
            } else {
                findViewById<TextView>(R.id.hintText).text = "Podana liczba jest za duża."
            }

            findViewById<EditText>(R.id.textInput).setText("")
        } catch (e: NumberFormatException) {

        }


    }
}