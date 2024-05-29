package fr.vannes.ecoboat.ui.home;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

/**
 * Custom view to draw a circular progress bar.
 */
public class CircularProgressBar extends View {

    // Initialize the progress value
    private int progress = 0;
    // Initialize the Paint object
    private final Paint paint = new Paint();

    /**
     * Constructor for the CircularProgressBar
     * @param context The Context the view is running in, through which it can access the current theme, resources, etc.
     * @param attrs The attributes of the XML tag that is inflating the view.
     */
    public CircularProgressBar(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        paint.setStrokeWidth(10);
        paint.setStyle(Paint.Style.STROKE);
    }

    /**
     * This method is called when the view should render its content.
     * @param canvas The canvas on which the background will be drawn
     */
    @Override
    protected void onDraw(@NonNull Canvas canvas) {
        // Call the superclass method
        super.onDraw(canvas);

        // Get the width and height of the view
        int width = getWidth();
        int height = getHeight();
        // Get the radius of the circle
        int radius = Math.min(width, height) / 2 - 10;
        // Get the center of the view
        int cx = width / 2;
        int cy = height / 2;

        // Draw the outer circle
        paint.setColor(0xFF000000); // Black color
        canvas.drawArc(cx - radius, cy - radius, cx + radius, cy + radius,
                360, 360, false, paint);

        // Draw the inner half circle
        int innerRadius = radius - 20; // Make the inner circle smaller

        // Change color based on the progress value
        if (progress <= 20) {
            paint.setColor(0xFFFF0000); // Red color
        } else if (progress <= 40) {
            paint.setColor(0xFFFF7F00); // Orange color
        } else if (progress <= 60) {
            paint.setColor(0xFFFFFF00); // Yellow color
        } else if (progress <= 80) {
            paint.setColor(0xFF00FF00); // Green color
        } else {
            paint.setColor(0xFF007FFF); // Blue color
        }

        // Draw the inner half circle based on the progress value
        float sweepAngle = (float) progress / 100 * 180;
        canvas.drawArc(cx - innerRadius, cy - innerRadius, cx + innerRadius, cy + innerRadius,
                180, sweepAngle, false, paint);

        // Draw the needle
        double angle = Math.toRadians(sweepAngle + 180); // Adjust the angle to start from the top of the circle
        float needleLengthFactor = 0.8f; // Reduce the needle length by 20%
        float needleX = cx + (float) (innerRadius * Math.cos(angle) * needleLengthFactor);
        float needleY = cy + (float) (innerRadius * Math.sin(angle) * needleLengthFactor);
        paint.setColor(0xFF000000); // Black color
        canvas.drawLine(cx, cy, needleX, needleY, paint);

        // Draw the progress text
        paint.setColor(0xFF000000); // Black color
        paint.setTextSize(80);
        String progressText = String.valueOf(progress);
        float textWidth = paint.measureText(progressText);

        // Draw background
        float textHeight = paint.descent() - paint.ascent();
        float textOffset = (textHeight / 2) - paint.descent();
        float backgroundMargin = 10f; // Adjust this value to change the background size
        float left = cx - textWidth / 2 - backgroundMargin;
        float top = cy - textOffset - backgroundMargin;
        float right = cx + textWidth / 2 + backgroundMargin;
        float bottom = cy + textOffset + backgroundMargin;
        paint.setColor(0xFFFFFFFF); // White color for the background
        canvas.drawRect(left, top, right, bottom, paint);

        // Draw text over the background
        paint.setColor(0xFF000000); // Black color
        canvas.drawText(progressText, cx - textWidth / 2, cy + textOffset, paint);

    }

    /**
     * Setter for the progress value
     * @param progress The new progress value
     */
    public void setProgress(int progress) {
        this.progress = progress;
        invalidate(); // Redraw the view
    }
}