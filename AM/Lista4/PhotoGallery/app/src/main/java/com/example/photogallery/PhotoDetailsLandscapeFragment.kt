package com.example.photogallery

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.RatingBar
import android.widget.TextView
import androidx.core.content.ContextCompat

class PhotoDetailsLandscapeFragment : Fragment() {

    private lateinit var imageView: ImageView
    private lateinit var description: TextView
    private lateinit var ratingBar: RatingBar

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.fragment_photo_details_landscape, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        imageView = view.findViewById(R.id.imageView)
        description = view.findViewById(R.id.description)
        ratingBar = view.findViewById(R.id.ratingBar)

        val activity = requireActivity() as PhotoDetails
        val imageID = activity.getImageID()

        val imageCell: ImageCell? = ImageCell.imageCellsList.find { imageCell -> imageCell?.id == imageID }
        imageView.setImageDrawable(ContextCompat.getDrawable(requireContext(), imageCell?.image ?: R.drawable.black))
        description.text = imageCell?.description
        ratingBar.rating = imageCell!!.rating
        activity.setRatingBar(ratingBar)
    }

    override fun onDestroyView() {
        super.onDestroyView()

        val activity = requireActivity() as PhotoDetails
        activity.preserveRating = ratingBar.rating
    }
}