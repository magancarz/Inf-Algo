package com.example.customprogressbar.views

import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View

class CustomView : View {
    private var progress = 0.0f
    private var maxProgress = 100
    private var isTextVisible = true

    var remainingSeconds = ""

    private val progressColor = Color.BLUE
    private val backgroundColor = Color.GRAY

    private val progressPaint = Paint(Paint.ANTI_ALIAS_FLAG).apply {
        style = Paint.Style.STROKE
        strokeWidth = 20f
        color = progressColor
    }

    private val backgroundPaint = Paint(Paint.ANTI_ALIAS_FLAG).apply {
        style = Paint.Style.STROKE
        strokeWidth = 20f
        color = backgroundColor
    }

    private val textPaint = Paint()

    private val ovalBounds = RectF()

    constructor(context: Context) : super(context)
    constructor(context: Context, attrs: AttributeSet?) : super(context, attrs)

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)

        val centerX = width / 2f
        val centerY = height / 2f
        val radius = (Math.min(width, height) - progressPaint.strokeWidth) / 2f

        ovalBounds.set(centerX - radius, centerY - radius, centerX + radius, centerY + radius)

        canvas.drawArc(ovalBounds, 0f, 360f, false, backgroundPaint)

        val sweepAngle = 360f * progress / maxProgress
        canvas.drawArc(ovalBounds, -90f, sweepAngle, false, progressPaint)

        var text = remainingSeconds

        if (text=="0") text = "END"

        if (isTextVisible)
        {
            val textBounds = Rect()
            textPaint.getTextBounds(text, 0, text.length, textBounds)
            val textWidth = textPaint.measureText(text)
            val textHeight = textBounds.height()

            val textX = centerX
            val textY = centerY + textHeight / 2f

            textPaint.textSize = determineTextSize(text)
            textPaint.color = progressColor
            canvas.drawText(text, textX - text.length * 20, textY, textPaint)
        }
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        if (event.action == MotionEvent.ACTION_DOWN) {
            isTextVisible = !isTextVisible
            invalidate()
        }
        return super.onTouchEvent(event)
    }

    private fun determineTextSize(text: String): Float {
        val bounds = Rect()
        val maxWidth = width * 0.8f

        var textSize = 70f
        textPaint.textSize = textSize

        while (textPaint.measureText(text) > maxWidth) {
            textSize -= 1f
            textPaint.textSize = textSize
        }

        return textSize
    }

    fun setProgress(progress: Float) {
        this.progress = progress
        invalidate()
    }

    fun setMaxProgress(maxProgress: Int) {
        this.maxProgress = maxProgress
        invalidate()
    }
}