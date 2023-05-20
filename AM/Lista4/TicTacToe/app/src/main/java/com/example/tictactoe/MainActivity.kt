package com.example.tictactoe

import android.annotation.SuppressLint
import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.sp
import com.example.tictactoe.ui.theme.TicTacToeTheme

class MainActivity : ComponentActivity() {

    private val mainViewModel by viewModels<MainViewModel>()

    @SuppressLint("UnusedMaterialScaffoldPaddingParameter")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            TicTacToeTheme {
                Scaffold() {
                    Surface(color = MaterialTheme.colors.background) {ą
                        Column(
                            modifier = Modifier.fillMaxHeight(),
                            verticalArrangement = Arrangement.SpaceAround,
                            horizontalAlignment = Alignment.CenterHorizontally
                        ) {
                            ButtonGrid(board = mainViewModel.board, mainViewModel.boardSize, mainViewModel::play)

                            if (mainViewModel.isGameOver) {
                                Box {
                                    Text(
                                        text = "Game is over: ${mainViewModel.winner}",
                                        fontSize = 20.sp
                                    )
                                }
                            }

                            ResetButton(onClick = mainViewModel::reset)

                            if (mainViewModel.beforeGame) {
                                SizeDropdownList()
                            }
                        }
                    }
                }
            }
        }
    }
    @OptIn(ExperimentalMaterialApi::class)
    @Composable
    fun SizeDropdownList() {
        val listItems = arrayOf("3x3", "5x5", "7x7", "9x9", "11x11", "13x13", "15x15", "17x17", "19x19", "21x21")

        var expanded by remember {
            mutableStateOf(false)
        }

        var selectedItem by remember {
            mutableStateOf(listItems[0])
        }

        ExposedDropdownMenuBox(
            expanded = expanded,
            onExpandedChange = {
                expanded = !expanded
            }
        ) {
            TextField(
                value = selectedItem,
                onValueChange = {},
                readOnly = true,
                label = { Text(text = "Label") },
                trailingIcon = {
                    ExposedDropdownMenuDefaults.TrailingIcon(
                        expanded = expanded
                    )
                },
                colors = ExposedDropdownMenuDefaults.textFieldColors()
            )

            ExposedDropdownMenu(
                expanded = expanded,
                onDismissRequest = { expanded = false }
            ) {
                listItems.forEach { selectedOption ->

                    DropdownMenuItem(onClick = {
                        selectedItem = selectedOption
                        mainViewModel.startGame(selectedItem)
                        expanded = false
                    }) {
                        Text(text = selectedOption)
                    }
                }
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    TicTacToeTheme {
        Column(horizontalAlignment = Alignment.CenterHorizontally) {
            ButtonGrid(board = arrayListOf("X", "O", "X", "O", "O", "X", "", "X", "O"), 3) {}
            ResetButton {}
        }
    }
}