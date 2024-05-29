package fr.vannes.ecoboat.ui.nitrate;

import androidx.core.content.ContextCompat;
import androidx.lifecycle.ViewModelProvider;

import android.graphics.Color;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;

import java.util.ArrayList;
import java.util.List;

import fr.vannes.ecoboat.R;
import fr.vannes.ecoboat.databinding.FragmentNitrateBinding;

/**
 * NitrateFragment class
 */
public class NitrateFragment extends Fragment {

    // Link the NitrateViewModel to the NitrateFragment's layout
    private FragmentNitrateBinding binding;

    /**
     * Method to create a new instance of the NitrateFragment
     *
     * @return The new instance of the NitrateFragment
     */
    public static NitrateFragment newInstance() {
        return new NitrateFragment();
    }


    /**
     * This method is called when the fragment is created.
     * @param inflater The LayoutInflater object that can be used to inflate
     * any views in the fragment,
     * @param container If non-null, this is the parent view that the fragment's
     * UI should be attached to.  The fragment should not add the view itself,
     * but this can be used to generate the LayoutParams of the view.
     * @param savedInstanceState If non-null, this fragment is being re-constructed
     * from a previous saved state as given here.
     *
     * @return Return the View for the fragment's UI, or null.
     */
@Override
public View onCreateView(@NonNull LayoutInflater inflater,
                         @Nullable ViewGroup container,
                         @Nullable Bundle savedInstanceState) {

    // Call the ViewModelProvider to create a new instance of the NitrateViewModel
    NitrateViewModel nitrateViewModel =
            new ViewModelProvider(this).get(NitrateViewModel.class);

    // Inflate the layout for this fragment
    binding = FragmentNitrateBinding.inflate(inflater, container, false);
    View root = binding.getRoot();

    // Observe the LiveData from the NitrateViewModel
    final TextView textView = binding.textNitrate;
    nitrateViewModel.getText().observe(getViewLifecycleOwner(), textView::setText);

    final TextView textViewSubtitle = binding.chartLabel;
    nitrateViewModel.getSubtitle().observe(getViewLifecycleOwner(), textViewSubtitle::setText);

    // Create the LineChart
    final LineChart lineChart = binding.chart;

// Observe the LiveData from the NitrateViewModel
nitrateViewModel.getNitrate().observe(getViewLifecycleOwner(), nitrate -> {
    Log.d("NitrateFragment", "Received nitrate data: " + nitrate);
    // Create the entries for the LineChart
    List<Entry> entries = new ArrayList<>();
    for (int i = 0; i < nitrate.size(); i++) {
        // Convert the nitrate value to a float
        float nitrateValue = Float.parseFloat(nitrate.get(i));
        // Create a new entry with the nitrate value and add it to the entries list
        entries.add(new Entry(i, nitrateValue));
    }

    Log.d("NitrateFragment", "Nitrate entries created: " + entries);

    // Create the LineDataSet and LineData
    LineDataSet lineDataSet = new LineDataSet(entries, "Nitrate");
    LineData lineData = new LineData(lineDataSet);
    // Set the LineData to the LineChart
    lineChart.setData(lineData);
    lineChart.invalidate();

    Log.d("NitrateFragment", "Chart data set and invalidated");
});

// Button to refresh the nitrate data
binding.refreshButton.setBackgroundResource(R.drawable.cell_border);
binding.refreshButton.setOnClickListener(v -> {
    try {
        Log.d("NitrateFragment", "Refresh button clicked, fetching nitrate data");
        nitrateViewModel.fetchNitrate();
    } catch (Exception e) {
        Log.e("NitrateFragment", "Error fetching nitrate data: " + e);
    }
});


    // Return the root view
    return root;
}
    /**
     * This method is called when the fragment is destroyed.
     */
    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }


}