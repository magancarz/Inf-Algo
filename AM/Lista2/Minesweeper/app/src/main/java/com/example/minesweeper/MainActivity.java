package com.example.minesweeper;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements OnCellClickListener {

    GameController gameController;
    RecyclerView recyclerView;
    GridRecyclerAdapter gridRecyclerAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        recyclerView = findViewById(R.id.activity_main_grid);
        recyclerView.setLayoutManager(new GridLayoutManager(this, 10));

        gameController = new GameController(10);

        gridRecyclerAdapter = new GridRecyclerAdapter(gameController.getGrid().getCells(), this);
        recyclerView.setAdapter(gridRecyclerAdapter);
    }

    @Override
    public void onCellClick(Cell cell) {
        Toast.makeText(getApplicationContext(), "Cell clicked", Toast.LENGTH_SHORT).show();
    }
}