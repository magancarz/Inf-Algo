package com.example.minesweeper;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements OnCellClickListener {

    GameController gameController;
    RecyclerView recyclerView;
    GridRecyclerAdapter gridRecyclerAdapter;
    TextView play, flag, flagsCount;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        flag = findViewById(R.id.activity_main_flag);
        flagsCount = findViewById(R.id.activity_main_flagsleft);
        flag.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                gameController.toggleMode();
                if (gameController.isFlagMode()) {
                    GradientDrawable border = new GradientDrawable();
                    border.setColor(0xFFFFFFFF);
                    border.setStroke(1, 0xFF000000);
                    flag.setBackground(border);
                } else {
                    GradientDrawable border = new GradientDrawable();
                    border.setColor(0xFFFFFFFF);
                    flag.setBackground(border);
                }
            }
        });

        play = findViewById(R.id.activity_main_smiley);
        play.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                gameController = new GameController(10, 10);
                gridRecyclerAdapter.setCells(gameController.getGrid().getCells());
            }
        });

        recyclerView = findViewById(R.id.activity_main_grid);
        recyclerView.setLayoutManager(new GridLayoutManager(this, 10));

        gameController = new GameController(10, 10);

        gridRecyclerAdapter = new GridRecyclerAdapter(gameController.getGrid().getCells(), this);
        recyclerView.setAdapter(gridRecyclerAdapter);
        flagsCount.setText(String.format("%03d", gameController.getNumberOfBombs() - gameController.getFlagCount()));
    }

    @Override
    public void onCellClick(Cell cell) {
        gameController.handleCellClick(cell);

        flagsCount.setText(String.format("%03d", gameController.getNumberOfBombs() - gameController.getFlagCount()));

        if (gameController.isGameOver()) {
            Toast.makeText(getApplicationContext(), "Game over!", Toast.LENGTH_SHORT).show();
            gameController.getGrid().revealAllBombs();
        } else if (gameController.isGameWon()) {
            Toast.makeText(getApplicationContext(), "Game won!", Toast.LENGTH_SHORT).show();
            gameController.getGrid().revealAllBombs();
        }

        gridRecyclerAdapter.setCells(gameController.getGrid().getCells());
    }
}