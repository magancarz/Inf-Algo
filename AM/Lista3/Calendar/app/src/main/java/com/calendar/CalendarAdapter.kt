package com.calendar

import android.graphics.Color
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import java.time.LocalDate

class CalendarAdapter(
    private val daysOfMonth: ArrayList<LocalDate?>,
    private val onItemListener: OnItemListener,
    private val selectedDate: LocalDate?,
) : RecyclerView.Adapter<CalendarViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CalendarViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val view: View = inflater.inflate(R.layout.calendar_cell, parent, false)
        val layoutParams = view.layoutParams
        layoutParams.height = (parent.height * 0.166666666).toInt()
        return CalendarViewHolder(view, onItemListener, daysOfMonth)
    }

    override fun onBindViewHolder(holder: CalendarViewHolder, position: Int) {
        val date: LocalDate? = daysOfMonth[position]
        if (date != null) {
            holder.dayOfMonth.text = date.dayOfMonth.toString()
            if (date == selectedDate) holder.parentView.setBackgroundColor(Color.LTGRAY)
        } else {
            holder.dayOfMonth.text = ""
        }
    }

    override fun getItemCount(): Int {
        return daysOfMonth.size
    }

    interface OnItemListener {
        fun onItemClick(position: Int, date: LocalDate?)
    }
}