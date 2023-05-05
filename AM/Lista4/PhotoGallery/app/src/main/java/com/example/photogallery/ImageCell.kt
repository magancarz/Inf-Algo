package com.example.photogallery

class ImageCell(
    var image: Int,
    var description: String,
    var rating: Float,
    var id: Int
) {

    companion object {
        var imageCellsList: ArrayList<ImageCell?> = ArrayList()
    }
}