package com.calendar

import java.time.LocalTime

class Event(name: String, date: String?) {

    private var title: String?
    private var date: String?

    init {
        this.title = name
        this.date = date
    }

    fun getDate(): String? {
        return date
    }

    fun getTitle(): String? {
        return title
    }

    companion object {
        var eventsList: ArrayList<Event> = ArrayList()
    }
}