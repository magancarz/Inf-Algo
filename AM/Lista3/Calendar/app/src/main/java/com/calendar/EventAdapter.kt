package com.calendar

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.TextView

class EventAdapter(context: Context, private val events: List<Event>) :
    ArrayAdapter<Event>(context, 0, events) {

    override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
        var view = convertView
        val event = getItem(position)

        if (view == null) {
            view = LayoutInflater.from(context).inflate(R.layout.event_cell, parent, false)
        }

        val eventCell = view!!.findViewById<TextView>(R.id.eventCell)

        val eventTitle = event!!.name + " " + event.getDate()
        eventCell.text = eventTitle

        return view
    }
}