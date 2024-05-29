package fr.vannes.ecoboat.ui.home;

import android.os.Build;
import android.os.Handler;
import android.util.Log;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.concurrent.TimeUnit;

import fr.vannes.ecoboat.utils.Utils;

/**
 * ViewModel for the home fragment.
 */
public class HomeViewModel extends ViewModel {

    // Initialize the temperature value
    private double temperatureValue;
    // Initialize the nitrate value
    private double nitrateValue;
    // Initialize the pH value
    private double phValue;

    // Live data to store the text
    private final MutableLiveData<String> mText;
    // Live data to store the index
    private final MutableLiveData<Integer> mIndex;
    // LiveData for water quality text
    private final MutableLiveData<String> mWaterQualityText;
    // LiveData for location
    private final MutableLiveData<String> mLocation;
    // Defining a Handler to manage messages and tasks on the main (UI) thread.
    private final Handler handler = new Handler();
    // Runnable to update the date every minute
    private final Runnable updateDateRunnable = new Runnable() {
        @Override
        public void run() {
            updateDate();
            handler.postDelayed(this, TimeUnit.MINUTES.toMillis(1)); // Update the date every minute
        }
    };


    /**
     * Constructor for the HomeViewModel
     */
    public HomeViewModel() {
        mText = new MutableLiveData<>();
        String text = "Qualité de l'eau en ce moment :\n";
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            text += " " + getCurrentDateFormatted();
        }
        mText.setValue(text);

        mIndex = new MutableLiveData<>();

        // Update the water quality index
        updateWaterQuality();


        mWaterQualityText = new MutableLiveData<>(); // Initialize the new LiveData


        mLocation = new MutableLiveData<>();
//
//        // TODO Change this value with the API value
//        mLocation.setValue("Vannes, Morbihan, France");
//        mLocation.setValue(this.getLocation().getValue());


        handler.post(updateDateRunnable);

    }

    /**
     * Method to update the water quality
     */
    public void updateWaterQuality() {
        int waterQuality = Utils.calculateWaterQuality(temperatureValue, phValue, nitrateValue);
        mIndex.setValue(waterQuality);
    }

    /**
     * Getter for the text
     *
     * @return the LiveData of the text
     */
    public LiveData<String> getText() {
        return mText;
    }

    /**
     * Getter for the index
     *
     * @return the LiveData of the index
     */
    public LiveData<Integer> getIndex() {
        return mIndex;
    }

    /**
     * Getter for the water quality text
     *
     * @return the LiveData of the water quality text
     */
    public LiveData<String> getWaterQualityText() { // Getter for the new LiveData
        return mWaterQualityText;
    }

    /**
     * Getter for the location
     *
     * @return the LiveData of the location
     */
    public LiveData<String> getLocation() {
        return mLocation;
    }

    /**
     * Get the current date formatted
     *
     * @return the current french date formatted as a string
     */
    private String getCurrentDateFormatted() {
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy HH:mm", Locale.FRANCE);
        return sdf.format(new Date());
    }

    /**
     * Update the date in the LiveData
     */
    private void updateDate() {
        String text = "Qualité de l'eau en ce moment :\n";
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            text += " " + getCurrentDateFormatted();
        }
        mText.setValue(text);
    }


    /**
     * Getter for the temperature value
     *
     * @return the temperature value
     */
    public double getTemperatureValue() {
        return this.temperatureValue;
    }

    /**
     * Getter for the pH value
     *
     * @return the pH value
     */
    public double getPhValue() {
        return this.phValue;
    }

    /**
     * Getter for the nitrate value
     *
     * @return the nitrate value
     */
    public double getNitrateValue() {
        return this.nitrateValue;
    }



    /**
     * Setter for the temperature value
     *
     * @param temperatureValue the temperature value
     */
    public void setTemperatureValue(double temperatureValue) {
        this.temperatureValue = temperatureValue;
    }

    /**
     * Setter for the pH value
     *
     * @param phValue the pH value
     */
    public void setPhValue(double phValue) {
        this.phValue = phValue;
    }

    /**
     * Setter for the nitrate value
     *
     * @param nitrateValue the nitrate value
     */
    public void setNitrateValue(double nitrateValue) {
        this.nitrateValue = nitrateValue;
    }

    /**
     * Setter for the location
     *
     * @param location the location
     */
    public void setLocation(String location) {
        Log.d("HomeViewModel", "Setting location: " + location); // Log the location value
        mLocation.setValue(location);
    }



    /**
     * Stop the updates when the ViewModel is cleared
     */
    @Override
    protected void onCleared() {
        super.onCleared();
        handler.removeCallbacks(updateDateRunnable); // Stop the updates when the ViewModel is cleared
    }
}