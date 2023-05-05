package com.example.photogallery

import android.annotation.SuppressLint
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.calendar.ImageCellAdapter

class MainActivity : AppCompatActivity(), ImageCellAdapter.OnEventClickListener {

    private var imagesRecyclerView: RecyclerView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if (ImageCell.imageCellsList.isEmpty()) {
            ImageCell.imageCellsList.add(ImageCell(R.drawable.black, "black", 1f, 0))
            ImageCell.imageCellsList.add(ImageCell(R.drawable.green, "green", 2f, 1))
            ImageCell.imageCellsList.add(ImageCell(R.drawable.orange, "orange", 3f, 2))
            ImageCell.imageCellsList.add(ImageCell(R.drawable.red, "red", 4f, 3))
            ImageCell.imageCellsList.add(ImageCell(R.drawable.purple, "purple", 5f, 4))
        }

        imagesRecyclerView = findViewById(R.id.imagesRecyclerView)

        val imageCellsAdapter = ImageCellAdapter(applicationContext, ImageCell.imageCellsList, this)
        val layoutManager: RecyclerView.LayoutManager = LinearLayoutManager(applicationContext)
        imagesRecyclerView!!.layoutManager = layoutManager
        imagesRecyclerView!!.adapter = imageCellsAdapter
    }

    override fun onResume() {
        super.onResume()

        val bundle: Bundle = intent.extras ?: return

        val imageID = bundle!!.getInt("imageID")
        val rating = bundle!!.getFloat("rating")

        val imageCell: ImageCell? = ImageCell.imageCellsList.find { imageCell -> imageCell!!.id == imageID }
        imageCell!!.rating = rating

        ImageCell.imageCellsList.sortByDescending { imageCell -> imageCell!!.rating }

        val imageCellsAdapter = ImageCellAdapter(applicationContext, ImageCell.imageCellsList, this)
        val layoutManager: RecyclerView.LayoutManager = LinearLayoutManager(applicationContext)
        imagesRecyclerView!!.layoutManager = layoutManager
        imagesRecyclerView!!.adapter = imageCellsAdapter
    }

    override fun onEventClick(imageCell: ImageCell?) {
        val intent = Intent(this, PhotoDetails::class.java)
        intent.putExtra("imageID", imageCell!!.id)
        startActivity(intent)
    }
}