package com.calendar

import android.content.Context
import android.view.View
import android.widget.ImageView
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.RecyclerView
import com.example.photogallery.ImageCell
import com.example.photogallery.MainActivity
import com.example.photogallery.R

class ImageCellViewHolder(
    private val context: Context,
    itemView: View,
    onItemListener: ImageCellAdapter.OnEventClickListener,
    private var imageCells: java.util.ArrayList<ImageCell?>
) : RecyclerView.ViewHolder(itemView), View.OnClickListener {

    var imageView: ImageView? = null
    var textView: TextView? = null

    val onItemListener: ImageCellAdapter.OnEventClickListener

    var imageCell: ImageCell? = null

    init {
        imageView = itemView.findViewById(R.id.imageView)
        textView = itemView.findViewById(R.id.description)
        this.onItemListener = onItemListener
    }

    fun setContent(id: Int) {
        imageCell = imageCells[id]

        imageView!!.setImageDrawable(ContextCompat.getDrawable(context, imageCell!!.image))
        imageView!!.setOnClickListener(this)
        textView!!.text = imageCell!!.description
    }

    override fun onClick(view: View) {
        onItemListener.onEventClick(imageCell)
    }
}
