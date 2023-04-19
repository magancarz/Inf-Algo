package com.calendar

import android.view.View
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.calendar.CalendarAdapter.OnItemListener
import java.time.LocalDate

class CalendarViewHolder(
    itemView: View,
    onItemListener: OnItemListener,
    private val daysOfMonth: ArrayList<LocalDate?>,
) : RecyclerView.ViewHolder(itemView), View.OnClickListener {

    val dayOfMonth: TextView
    private val onItemListener: OnItemListener
    val parentView: View

    init {
        dayOfMonth = itemView.findViewById(R.id.cellDayText)
        parentView = itemView.findViewById(R.id.parentView)
        this.onItemListener = onItemListener
        itemView.setOnClickListener(this)
    }

    override fun onClick(view: View) {
        onItemListener.onItemClick(adapterPosition, daysOfMonth[adapterPosition])
    }
}