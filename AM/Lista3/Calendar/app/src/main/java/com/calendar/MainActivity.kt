package com.calendar

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.ListView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.RecyclerView
import java.time.LocalDate
import java.time.YearMonth
import java.time.format.DateTimeFormatter

class MainActivity : AppCompatActivity(), CalendarAdapter.OnItemListener {

    private var monthYearText: TextView? = null
    private var calendarRecyclerView: RecyclerView? = null
    private var selectedDate: LocalDate? = null
    private var eventListView: ListView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_main)

        if (selectedDate == null) selectedDate = LocalDate.now()

        initWidgets()
        setMonthView()
    }

    private fun initWidgets() {
        calendarRecyclerView = findViewById(R.id.calendarRecyclerView)
        monthYearText = findViewById(R.id.monthYearTV)
        eventListView = findViewById(R.id.eventListView)
    }

    private fun setMonthView() {
        monthYearText!!.text = monthYearFromDate(selectedDate)
        val daysInMonth = daysInMonthArray(selectedDate)
        val calendarAdapter = CalendarAdapter(daysInMonth, this, selectedDate)
        val layoutManager: RecyclerView.LayoutManager = GridLayoutManager(applicationContext, 7)
        calendarRecyclerView!!.layoutManager = layoutManager
        calendarRecyclerView!!.adapter = calendarAdapter
        setEventAdapter()
    }

    private fun daysInMonthArray(date: LocalDate?): ArrayList<LocalDate?> {
        val daysInMonthArray: ArrayList<LocalDate?> = ArrayList()
        val yearMonth: YearMonth = YearMonth.from(date)
        val daysInMonth: Int = yearMonth.lengthOfMonth()
        val firstOfMonth: LocalDate = selectedDate!!.withDayOfMonth(1)
        val dayOfWeek = firstOfMonth.dayOfWeek.value
        for (i in 1..42) {
            if (i <= dayOfWeek || i > daysInMonth + dayOfWeek) daysInMonthArray.add(null) else daysInMonthArray.add(
                LocalDate.of(
                    selectedDate!!.year, selectedDate!!.month, i - dayOfWeek
                )
            )
        }
        return daysInMonthArray
    }

    private fun monthYearFromDate(date: LocalDate?): String {
        val formatter = DateTimeFormatter.ofPattern("MMMM yyyy")
        return date!!.format(formatter)
    }

    fun previousMonthAction(view: View?) {
        selectedDate = selectedDate!!.minusMonths(1)
        setMonthView()
    }

    fun nextMonthAction(view: View?) {
        selectedDate = selectedDate!!.plusMonths(1)
        setMonthView()
    }

    fun newEventAction(view: View?) {
        val intent = Intent(this, EventEditActivity::class.java)
        intent.putExtra("selectedDate", selectedDate.toString())
        startActivity(intent)
    }

    override fun onItemClick(position: Int, date: LocalDate?) {
        if (date != null) {
            selectedDate = date
            setMonthView()
        }
    }

    override fun onResume() {
        super.onResume()
        setEventAdapter()
    }

    private fun setEventAdapter() {
        val dailyEvents: ArrayList<Event> = Event.eventsList
        val eventAdapter = EventAdapter(applicationContext, dailyEvents)
        eventListView!!.adapter = eventAdapter
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        outState.putString("selectedDate", selectedDate.toString())
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        selectedDate = LocalDate.parse(savedInstanceState.getString("selectedDate"))
>>>>>>> 7123d98 (AM Lista 3: nie final)
    }
}