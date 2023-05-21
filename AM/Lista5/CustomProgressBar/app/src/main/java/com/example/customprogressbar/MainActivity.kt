package com.example.customprogressbar

import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.widget.Button
import android.widget.SeekBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.customprogressbar.views.CustomView

class MainActivity : AppCompatActivity() {

    private var selectedHours = 0
    private var selectedMinutes = 0
    private var selectedSeconds = 0
    private var isProgressStarted = false

    private lateinit var progressBar: CustomView
    private lateinit var sliderHours: SeekBar
    private lateinit var sliderValueHours: TextView
    private lateinit var cancelButton: Button

    private lateinit var sliderMinutes: SeekBar
    private lateinit var sliderValueMinutes: TextView

    private lateinit var sliderSeconds: SeekBar
    private lateinit var sliderValueSeconds: TextView

    private val handler = Handler(Looper.getMainLooper())
    private var currentProgress = 0.0f
    private val maxProgress = 100

    private var secondsOnStart = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        progressBar = findViewById(R.id.progressBar)

        cancelButton = findViewById(R.id.cancel)
        cancelButton.setOnClickListener {
            cancelProgress()
        }

        val button = findViewById<Button>(R.id.button)
        button.setOnClickListener {
            isProgressStarted = true
            startProgress()
        }

        sliderHours = findViewById(R.id.sliderHours)
        sliderValueHours = findViewById(R.id.sliderValueHours)

        sliderMinutes = findViewById(R.id.sliderMinutes)
        sliderValueMinutes = findViewById(R.id.sliderValueMinutes)

        sliderSeconds = findViewById(R.id.sliderSeconds)
        sliderValueSeconds = findViewById(R.id.sliderValueSeconds)

        sliderHours.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sliderValueHours.text = progress.toString()
                selectedHours = progress
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {

            }

            override fun onStopTrackingTouch(seekBar: SeekBar?) {

            }
        })

        sliderMinutes.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sliderValueMinutes.text = progress.toString()
                selectedMinutes = progress
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {

            }

            override fun onStopTrackingTouch(seekBar: SeekBar?) {

            }
        })

        sliderSeconds.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sliderValueSeconds.text = progress.toString()
                selectedSeconds = progress
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {

            }

            override fun onStopTrackingTouch(seekBar: SeekBar?) {

            }
        })

    }

    private fun startProgress() {
        cancelButton.isEnabled = true

        sliderHours.isEnabled = false
        sliderMinutes.isEnabled = false
        sliderSeconds.isEnabled = false

        currentProgress = 0.0f
        progressBar.setProgress(currentProgress)

        secondsOnStart = ((selectedHours.toFloat() * 3600.0f + selectedMinutes.toFloat() * 60.0f + selectedSeconds).toInt())

        updateCustomView()

        handler.postDelayed(updateProgressRunnable, 1000)
    }

    private fun cancelProgress() {
        currentProgress = 0.0f
        progressBar.setProgress(currentProgress)
        progressBar.remainingSeconds = ""

        sliderHours.isEnabled = true
        sliderMinutes.isEnabled = true
        sliderSeconds.isEnabled = true

        sliderHours.progress = 0
        sliderMinutes.progress = 0
        sliderSeconds.progress = 0
        selectedHours = 0
        selectedMinutes = 0
        selectedSeconds = 0
        sliderValueHours.text = "0"
        sliderValueMinutes.text = "0"
        sliderValueSeconds.text = "0"
        handler.removeCallbacks(updateProgressRunnable)

        cancelButton.isEnabled = false
    }

    private fun updateCustomView() {
        if (isProgressStarted) {
            val totalSeconds = selectedHours * 3600 + selectedMinutes * 60 + selectedSeconds
            val maxTotalSeconds = 24 * 3600

            val progress = (totalSeconds.toFloat() / maxTotalSeconds * 100)
            progressBar.setProgress(progress)
        }
    }

    private val updateProgressRunnable = object : Runnable {
        override fun run() {
            currentProgress += (1.0f / (selectedHours.toFloat() * 3600.0f + selectedMinutes.toFloat() * 60.0f + selectedSeconds)) * 100
            progressBar.setProgress(currentProgress)

            secondsOnStart--
            progressBar.remainingSeconds = secondsOnStart.toString()

            if (currentProgress < maxProgress) {
                handler.postDelayed(this, 1000)
            }
        }
    }
}