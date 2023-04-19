package com.calendar

import java.time.LocalTime

class Event(var name: String, date: String?, time: LocalTime) {

    private var date: String?
    private var time: LocalTime

    init {
        this.date = date
        this.time = time
    }

    fun getDate(): String? {
        return date
    }

    fun setDate(date: String?) {
        this.date = date
    }

    companion object {
        var eventsList: ArrayList<Event> = ArrayList()
    }
}