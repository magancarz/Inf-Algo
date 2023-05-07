package com.example.photogallery

import android.content.Intent
import android.content.res.Configuration
import android.os.Bundle
import android.view.View
import android.widget.ImageView
import android.widget.RatingBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentContainerView

class PhotoDetails : AppCompatActivity() {

    private var imageID: Int = 0
    private var rating: RatingBar? = null
    var preserveRating: Float = 0f

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_photo_details)

        val bundle: Bundle? = intent.extras
        imageID = bundle!!.getInt("imageID")

        if (savedInstanceState == null) {
            val currentOrientation = resources.configuration.orientation
            if (currentOrientation == Configuration.ORIENTATION_PORTRAIT) {
                replaceFragment(PhotoDetailsFragment())
            } else if (currentOrientation == Configuration.ORIENTATION_LANDSCAPE) {
                replaceFragment(PhotoDetailsLandscapeFragment())
            }
        }
    }

    override fun onConfigurationChanged(newConfig: Configuration) {
        super.onConfigurationChanged(newConfig)

        var currentFragment = supportFragmentManager.findFragmentById(R.id.fragment_container_view)

        if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT && currentFragment !is PhotoDetailsFragment) {
            replaceFragment(PhotoDetailsFragment())
        } else if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE && currentFragment !is PhotoDetailsLandscapeFragment) {
            replaceFragment(PhotoDetailsLandscapeFragment())
        }
    }

    private fun replaceFragment(fragment: Fragment) {
        supportFragmentManager.beginTransaction()
            .replace(R.id.fragment_container_view, fragment)
            .commit()
    }

    fun getImageID(): Int {
        return imageID
    }

    fun setRatingBar(value: RatingBar?) {
        var currentRating = 0f
        if (rating != null) {
            currentRating = rating!!.rating
        }
        rating = value
        if (currentRating != 0f) {
            value!!.rating = currentRating
        }
    }

    fun goBackToGallery(view: View) {
        val intent = Intent(this, MainActivity::class.java)
        intent.putExtra("imageID", imageID)
        intent.putExtra("rating", rating!!.rating)
        startActivity(intent)
    }

}