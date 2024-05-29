package fr.vannes.ecoboat.ui.ph;

import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import java.util.List;
import java.util.Map;

import fr.vannes.ecoboat.utils.APIUtils;

/**
 * ViewModel for the Ph fragment.
 */
public class PhViewModel extends ViewModel {
    // Text attribute to display the fragment title
    private final MutableLiveData<String> mText;
    // Text attribute to display the subtitle
    private final MutableLiveData<String> mSubtitle;
    // pH attribute to display the pH
    private final MutableLiveData<List<Map<String, String>>> mPh;

    /**
     * Constructor for the PhViewModel
     */
    public PhViewModel() {
        mText = new MutableLiveData<>();
        mText.setValue("Derniers relevés de pH");

        mSubtitle = new MutableLiveData<>();
        mSubtitle.setValue("Derniers relevés de pH (en minutes écoulées)");

        mPh = new MutableLiveData<>();
        fetchPh();
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
     * Method to get the pH attribute
     * @return The pH attribute
     */
    public MutableLiveData<List<Map<String, String>>> getPh() {
        return mPh;
    }

    /**
     * Method to fetch the pH from the API
     * with the APIUtils getpH method
     */
    public void fetchPh() {
        // Create a new thread to fetch the pH from the API
        new Thread(() -> {
            // Get the pH from the API
            APIUtils apiUtils = new APIUtils();
            try{
                // Get the pH from the API
                List<Map<String, String>> ph = apiUtils.getpH();

                // Create a new Handler to update the LiveData on the main thread
                new Handler(Looper.getMainLooper()).post(() -> {
                    mPh.setValue(ph);
                });
            } catch (Exception e) {
                Log.e("PhViewModel", "Error while fetching the pH", e);
            }
        }).start();
    }


}