package com.example.photogallery

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.ContactsContract.CommonDataKinds.Im
import android.view.View
import android.widget.ImageView
import android.widget.RatingBar
import android.widget.TextView
import androidx.core.content.ContextCompat

class PhotoDetails : AppCompatActivity() {

    private var imageID: Int = 0

    private var imageView: ImageView? = null
    private var description: TextView? = null
    private var ratingBar: RatingBar? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_photo_details)

        val bundle: Bundle? = intent.extras
        imageID = bundle!!.getInt("imageID")

        imageView = findViewById(R.id.imageView)
        description = findViewById(R.id.description)
        ratingBar = findViewById(R.id.ratingBar)

        val imageCell: ImageCell? = ImageCell.imageCellsList.find { imageCell -> imageCell!!.id == imageID }
        imageView!!.setImageDrawable(ContextCompat.getDrawable(this, imageCell!!.image))
        description!!.text = imageCell.description
    }

    fun goBackToGallery(view: View) {
        val intent = Intent(this, MainActivity::class.java)
        intent.putExtra("imageID", imageID)
        intent.putExtra("rating", ratingBar!!.rating)
        startActivity(intent)
    }

}