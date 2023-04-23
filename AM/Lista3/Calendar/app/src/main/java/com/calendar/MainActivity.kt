package com.calendar

import android.Manifest
import android.app.AlarmManager
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.os.SystemClock
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import java.time.LocalDate
import java.time.YearMonth
import java.time.format.DateTimeFormatter
import java.util.*


class MainActivity : AppCompatActivity(), CalendarAdapter.OnItemListener, EventAdapter.OnEventClickListener {

    private var monthYearText: TextView? = null
    private var calendarRecyclerView: RecyclerView? = null
    private var eventRecyclerView: RecyclerView? = null
    private var selectedDate: LocalDate? = null
    private var CHANNEL_ID = "reminder_channel_id"
    private var lastNotificationDate: String? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_main)

        if (selectedDate == null) selectedDate = LocalDate.now()

        //Test data
        if (Event.eventsList.size == 0) {
            Event.eventsList.add(Event("test1", LocalDate.now().toString()))
            Event.eventsList.add(Event("test2", LocalDate.of(2023, 5, 23).toString()))
        }

        if (lastNotificationDate == null) {
            lastNotificationDate = LocalDate.now().toString()
        }

        initWidgets()
        setMonthView()

        createNotificationChannel()
    }

    private fun initWidgets() {
        calendarRecyclerView = findViewById(R.id.calendarRecyclerView)
        eventRecyclerView = findViewById(R.id.eventRecyclerView)
        monthYearText = findViewById(R.id.monthYearTV)
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

    override fun onEventClick(title: TextView?) {
        val text = title!!.text;
        val title1 = text.split(" ")[0]
        val date = text.split(" ")[1]

        val el = Event.eventsList.find { event -> event.getTitle() == title1 && event.getDate() == date }
        Event.eventsList.remove(el)

        setEventAdapter()
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
        val eventAdapter = EventAdapter(dailyEvents, this)
        val layoutManager: RecyclerView.LayoutManager = LinearLayoutManager(applicationContext)
        eventRecyclerView!!.layoutManager = layoutManager
        eventRecyclerView!!.adapter = eventAdapter

        startNotify()
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        outState.putString("selectedDate", selectedDate.toString())
        outState.putString("lastNotificationDate", lastNotificationDate)
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        selectedDate = LocalDate.parse(savedInstanceState.getString("selectedDate"))
        lastNotificationDate = savedInstanceState.getString("lastNotificationDate")
        setMonthView()
    }

    private fun createNotificationChannel(){
        val name="Channel"
        val text="ChannelText"
        val importance = NotificationManager.IMPORTANCE_HIGH
        val channel = NotificationChannel(CHANNEL_ID, name, importance).apply {
            description = text
        }
        val notificationManager: NotificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        notificationManager.createNotificationChannel(channel)
    }

    private fun sendNotification(info:String, id:Int) {
        val builder = NotificationCompat.Builder(this, CHANNEL_ID)
            .setSmallIcon(R.drawable.time)
            .setContentTitle("Hej, przypominam o wydarzeniu")
            .setContentText(info)
            .setPriority(NotificationCompat.PRIORITY_HIGH)
        with(NotificationManagerCompat.from(this)) {
            if (ActivityCompat.checkSelfPermission(
                    this@MainActivity,
                    Manifest.permission.POST_NOTIFICATIONS
                ) != PackageManager.PERMISSION_GRANTED
            ) {
                return
            }
            notify(id, builder.build())
        }
    }

    private fun startNotify(){
        val myIntent = Intent(applicationContext, MyIntentService::class.java)
        val pendingIntent = PendingIntent.getService(applicationContext, 0, myIntent, PendingIntent.FLAG_IMMUTABLE)
        val alarmManager = getSystemService(ALARM_SERVICE) as AlarmManager

        val calendar = Calendar.getInstance()
        calendar.set(Calendar.HOUR_OF_DAY, 8)
        calendar.set(Calendar.MINUTE, 0)
        calendar.set(Calendar.SECOND, 0)

        alarmManager.setRepeating(
            AlarmManager.RTC_WAKEUP,
            calendar.timeInMillis,
            AlarmManager.INTERVAL_DAY,
            pendingIntent
        )

//        val alarmManager = getSystemService(ALARM_SERVICE) as AlarmManager
//        val triggerTime = SystemClock.elapsedRealtime() + 10000 // 10 seconds in milliseconds
//
//        alarmManager.setExact(
//            AlarmManager.ELAPSED_REALTIME_WAKEUP,
//            triggerTime,
//            pendingIntent
//        )
    }

}