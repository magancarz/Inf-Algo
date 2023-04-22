package com.calendar

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class EventAdapter(
    private val events: ArrayList<Event>,
    private val onEventClickListener: OnEventClickListener,
    ) : RecyclerView.Adapter<EventViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): EventViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val view: View = inflater.inflate(R.layout.event_cell, parent, false)
        return EventViewHolder(view, onEventClickListener, events)
    }

    override fun onBindViewHolder(holder: EventViewHolder, position: Int) {
        val event = events[position]
        holder.title.text = event.getTitle() + " " + event.getDate()
    }

    override fun getItemCount(): Int {
        return events!!.size
    }

    interface OnEventClickListener {
        fun onEventClick(title: TextView?)
    }
}