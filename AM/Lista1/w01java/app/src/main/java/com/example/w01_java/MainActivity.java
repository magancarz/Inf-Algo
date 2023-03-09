package com.example.w01_java;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private int r1 = 0;
    private int r2 = 0;
    private int score = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        score = 0;
        roll();
    }

    private void roll() {
        ((TextView)findViewById(R.id.points)).setText("Punkty: " + score);
        Random r = new Random();
        r1 = r.nextInt(10);
        r2 = r.nextInt(10);
        ((Button)findViewById(R.id.leftClick)).setText("" + r1);
        ((Button)findViewById(R.id.rightClick)).setText("" + r2);
    }

    public void buttonLeft(View view) {
        if (r1 >= r2) {
            score++;
            Toast.makeText(this, "Dobrze", Toast.LENGTH_SHORT).show();
        } else {
            score--;
            Toast.makeText(this, "Zle", Toast.LENGTH_SHORT).show();
        }

        roll();
    }

    public void buttonRight(View view) {
        if (r2 >= r1) {
            score++;
            Toast.makeText(this, "Dobrze", Toast.LENGTH_SHORT).show();
        } else {
            score--;
            Toast.makeText(this, "Zle", Toast.LENGTH_SHORT).show();
        }

        roll();
    }
}