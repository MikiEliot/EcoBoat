package fr.vannes.ecoboat.ui.nitrate;

import android.os.Handler;
import android.os.Looper;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.TimeUnit;

/**
 * ViewModel for the nitrate fragment.
 */
public class NitrateViewModel extends ViewModel {
    // Text attribute to display the fragment title
    private final MutableLiveData<String> mText;
    // Text attribute to display the subtitle
    private final MutableLiveData<String> mSubtitle;
    // nitrate attribute to display the nitrate
    private final MutableLiveData<List<String>> mNitrate;

    /**
     * Constructor for the NitrateViewModel
     */
    public NitrateViewModel() {
        mText = new MutableLiveData<>();
        mText.setValue("Derniers relevés de nitrate");

        mSubtitle = new MutableLiveData<>();
        mSubtitle.setValue("Derniers relevés de nitrate (en minutes écoulées)");

        mNitrate = new MutableLiveData<>();
        fetchNitrate();
    }

    /**
     * Method to get the text attribute
     * @return The text attribute
     */
    public MutableLiveData<String> getText() {
        return mText;
    }

    /**
     * Method to get the subtitle attribute
     * @return The subtitle attribute
     */
    public MutableLiveData<String> getSubtitle() {
        return mSubtitle;
    }

    /**
     * Method to get the nitrate attribute
     * @return The nitrate attribute
     */
    public MutableLiveData<List<String>> getNitrate() {
        return mNitrate;
    }

    /**
     * Method to fetch the nitrate from the API with the APIUtils getNitrate method
     * todo in the future we will use the APIUtils.getNitrate method
     */
    public void fetchNitrate() {
    // Create a fixed array of nitrate values
    String[] fixedNitrateValues = {"5", "8", "10", "12", "15", "18", "20", "22", "25", "28", "30", "32", "35", "38", "40", "42", "45", "48", "50", "55"};

    // Create a new list of nitrate
    List<String> nitrate = new ArrayList<>(Arrays.asList(fixedNitrateValues));

    // Update the LiveData with the new list of nitrate
    mNitrate.setValue(nitrate);
}


}