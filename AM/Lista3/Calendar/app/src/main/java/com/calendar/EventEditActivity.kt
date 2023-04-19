package com.calendar

import android.os.Bundle
import android.view.View
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import java.time.LocalTime


class EventEditActivity : AppCompatActivity() {

    private var name: EditText? = null
    private var selectedDate: String? = null
    private var localTime: LocalTime = LocalTime.now()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_event_edit)

        selectedDate = intent.getStringExtra("selectedDate")

        initWidgets()
    }

    private fun initWidgets() {
        name = findViewById(R.id.eventName)
    }

    fun saveEventAction(view: View?) {
        val eventName: String = name!!.text.toString()
        val newEvent = Event(eventName, selectedDate, localTime)
        Event.eventsList.add(newEvent)
        finish()
    }
}