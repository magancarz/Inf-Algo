package com.example.l1z2java;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private int currentValue = 0;
    private int score = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        rollValue();
    }

    private void rollValue() {
        Random r = new Random();
        currentValue = r.nextInt(100);
    }

    public void checkNumber(View view) {
        String value = ((EditText)findViewById(R.id.textInput)).getText().toString();

        if (value.isEmpty()) return;

        try {
            int compareValue = Integer.parseInt(value);
            if (currentValue == compareValue) {
                Toast.makeText(this, "Dobrzeeeee", Toast.LENGTH_SHORT).show();
                score++;
                rollValue();
            } else if (currentValue > compareValue) {
                ((TextView)findViewById(R.id.hintText)).setText("Podana liczba jest za mała.");
            } else {
                ((TextView)findViewById(R.id.hintText)).setText("Podana liczba jest za duża.");
            }

            ((EditText)findViewById(R.id.textInput)).setText("");
        } catch (NumberFormatException e) {

        }
    }
}