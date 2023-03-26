package com.example.minesweeper

import android.graphics.drawable.GradientDrawable
import android.os.Bundle
import android.view.View
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.RecyclerView
import org.w3c.dom.Text

class MainActivity : AppCompatActivity(), OnCellClickListener {

    var gameController: GameController? = null
    var recyclerView: RecyclerView? = null
    var gridRecyclerAdapter: GridRecyclerAdapter? = null
    var play: TextView? = null
    var flag: TextView? = null
    var flagsCount: TextView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        flag = findViewById(R.id.activity_main_flag)
        flagsCount = findViewById(R.id.activity_main_flagsleft)
        flag?.setOnClickListener(View.OnClickListener {
            gameController!!.toggleMode()
            if (gameController!!.isFlagMode) {
                val border = GradientDrawable()
                border.setColor(-0x1)
                border.setStroke(1, -0x1000000)
                flag?.setBackground(border)
            } else {
                val border = GradientDrawable()
                border.setColor(-0x1)
                flag?.setBackground(border)
            }
        })
        play = findViewById(R.id.activity_main_smiley)
        play?.setOnClickListener(View.OnClickListener {
            gameController = GameController(10, 10)
            gridRecyclerAdapter!!.setCells(gameController!!.grid.cells)
        })
        recyclerView = findViewById(R.id.activity_main_grid)
        recyclerView?.setLayoutManager(GridLayoutManager(this, 10))
        gameController = GameController(10, 10)
        gridRecyclerAdapter = GridRecyclerAdapter(gameController!!.grid.cells, this)
        recyclerView?.setAdapter(gridRecyclerAdapter)
        flagsCount?.setText(
            String.format(
                "%03d",
                gameController!!.numberOfBombs - gameController!!.flagCount
            )
        )
    }

    override fun onCellClick(cell: Cell?) {
        if (cell != null) {
            gameController!!.handleCellClick(cell)
        }
        flagsCount!!.text =
            String.format("%03d", gameController!!.numberOfBombs - gameController!!.flagCount)
        if (gameController!!.isGameOver) {
            Toast.makeText(applicationContext, "Game over!", Toast.LENGTH_SHORT).show()
            gameController!!.grid.revealAllBombs()
        } else if (gameController!!.isGameWon) {
            Toast.makeText(applicationContext, "Game won!", Toast.LENGTH_SHORT).show()
            gameController!!.grid.revealAllBombs()
        }
        gridRecyclerAdapter!!.setCells(gameController!!.grid.cells)
    }
}