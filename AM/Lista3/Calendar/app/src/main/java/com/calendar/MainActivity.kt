package com.calendar

import android.content.Context
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {

    private lateinit var recyclerView: RecyclerView
    private lateinit var adapter: CalendarAdapter
    private lateinit var dates: MutableList<String>

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        recyclerView = findViewById(R.id.calendarRecyclerView)
        recyclerView.layoutManager = LinearLayoutManager(this)

        dates = mutableListOf()
        // Add some sample dates to the list
        dates.add("01")
        dates.add("02")
        dates.add("03")
        dates.add("04")
        dates.add("05")
        dates.add("06")
        dates.add("07")
        dates.add("08")
        dates.add("09")
        dates.add("10")
        dates.add("11")
        dates.add("12")
        dates.add("13")
        dates.add("14")
        dates.add("15")
        dates.add("16")
        dates.add("17")
        dates.add("18")
        dates.add("19")
        dates.add("20")
        dates.add("21")
        dates.add("22")
        dates.add("23")
        dates.add("24")
        dates.add("25")
        dates.add("26")
        dates.add("27")
        dates.add("28")
        dates.add("29")
        dates.add("30")

        adapter = CalendarAdapter(this, dates)
        recyclerView.adapter = adapter
    }
}

class CalendarAdapter(private val context: Context, private val dates: List<String>)
    : RecyclerView.Adapter<CalendarAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.calendar_item, parent, false)
        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val date = dates[position]
        holder.dateTextView.text = date
    }

    override fun getItemCount(): Int {
        return dates.size
    }

    class ViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val dateTextView: TextView = view.findViewById(R.id.dateTextView)
    }
}