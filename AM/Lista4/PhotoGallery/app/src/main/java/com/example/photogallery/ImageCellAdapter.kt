package com.calendar

import android.app.Application
import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import androidx.recyclerview.widget.RecyclerView
import com.example.photogallery.ImageCell
import com.example.photogallery.R

class ImageCellAdapter(
    private val context: Context,
    private val imageCells: ArrayList<ImageCell?>,
    private val onEventClickListener: OnEventClickListener,
) : RecyclerView.Adapter<ImageCellViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ImageCellViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val view: View = inflater.inflate(R.layout.image_cell, parent, false)
        return ImageCellViewHolder(context, view, onEventClickListener, imageCells)
    }

    override fun onBindViewHolder(holder: ImageCellViewHolder, position: Int) {
        holder.setContent(position)
    }

    override fun getItemCount(): Int {
        return imageCells!!.size
    }

    interface OnEventClickListener {
        fun onEventClick(imageCell: ImageCell?)
    }
}