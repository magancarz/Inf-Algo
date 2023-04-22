package com.calendar

import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class EventViewHolder(
    itemView: View,
    onItemListener: EventAdapter.OnEventClickListener,
    private val events: ArrayList<Event>,
) : RecyclerView.ViewHolder(itemView), View.OnClickListener {

    val title: TextView
    val onItemListener: EventAdapter.OnEventClickListener

    var event: Event? = null

    init {
        title = itemView.findViewById(R.id.eventCell)
        this.onItemListener = onItemListener
        itemView.findViewById<TextView>(R.id.eventButton).setOnClickListener(this)
    }

    override fun onClick(view: View) {
        onItemListener.onEventClick(title)
    }
}