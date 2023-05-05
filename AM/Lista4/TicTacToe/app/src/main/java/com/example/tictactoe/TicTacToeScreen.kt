package com.example.tictactoe

import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.tictactoe.ui.theme.Purple500

@Composable
fun ResetButton(onClick: () -> Unit) {
    Button(onClick = onClick, modifier = Modifier
        .padding(16.dp)
        .height(50.dp)) {
        Text(
            text = "Restart",
            style = TextStyle(textAlign = TextAlign.Center),
            modifier = Modifier.fillMaxWidth()
        )
    }
}

@Composable
fun ButtonGrid(board: ArrayList<String>, size: Int, onclick: (Int) -> Unit) {

    val cellSize = 330.dp / size
    Column(verticalArrangement = Arrangement.SpaceEvenly) {
        for (i in 0 until size) {
            Row(horizontalArrangement = Arrangement.SpaceEvenly) {
                for (j in 0 until size) {
                    val index = i * size + j
                    TicTacToeButton(text = board[index], cellSize, { onclick(index) })
                }
            }
        }
    }
}

@Composable
fun TicTacToeButton(text: String, size: Dp, onclick: () -> Unit) {
    val color = if (text == "X") Color.Green else if (text == "O") Color.Red else Purple500;
    Box() {
        TextButton(
            border = BorderStroke(1.dp, color),
            onClick = onclick,
            enabled = text.isBlank(),
            modifier = Modifier.padding(1.dp).size(size)
        ) {
            Text(
                text = text,
                style = TextStyle(
                    fontSize = 15.sp
                )
            )
        }
    }
}