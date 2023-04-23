package com.calendar

import android.Manifest
import android.annotation.SuppressLint
import android.app.IntentService
import android.app.Notification
import android.app.PendingIntent
import android.content.Intent
import androidx.core.app.NotificationManagerCompat
import android.content.pm.PackageManager
import androidx.core.app.ActivityCompat
import androidx.core.app.NotificationCompat
import java.time.LocalDate


class MyIntentService : IntentService("MyIntentService") {
    override fun onHandleIntent(intent: Intent?) {
        val notifyIntent = Intent(applicationContext, MainActivity::class.java)
        val pendingIntent =
            PendingIntent.getActivity(applicationContext, 0, notifyIntent, PendingIntent.FLAG_IMMUTABLE)

        for (event in Event.eventsList) {
            if (event.getDate() != LocalDate.now().toString())
                continue

            val builder = NotificationCompat.Builder(applicationContext, "reminder_channel_id")
                .setSmallIcon(R.drawable.time)
                .setContentTitle("Event reminder")
                .setContentText(event.getTitle() + " " + event.getDate())
                .setPriority(NotificationCompat.PRIORITY_HIGH)
            builder.setContentIntent(pendingIntent)
            val notificationCompat: Notification = builder.build()
            val managerCompat = NotificationManagerCompat.from(applicationContext)
            if (ActivityCompat.checkSelfPermission(
                    applicationContext,
                    Manifest.permission.POST_NOTIFICATIONS
                ) != PackageManager.PERMISSION_GRANTED
            ) {
                return
            }
            managerCompat.notify(1, notificationCompat)
        }
    }

    companion object {
        private const val NOTIFICATION_ID = 3
    }
}