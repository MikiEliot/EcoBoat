package fr.vannes.ecoboat.ui.temperature;

import androidx.lifecycle.ViewModelProvider;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;

import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;

import fr.vannes.ecoboat.R;
import fr.vannes.ecoboat.databinding.FragmentTemperatureBinding;
import fr.vannes.ecoboat.utils.APIUtils;
import fr.vannes.ecoboat.utils.ChartUtils;

/**
 * Fragment to display the temperature.
 */
public class TemperatureFragment extends Fragment {

    // The binding for the fragment
    private FragmentTemperatureBinding binding;

    /**
     * Method to create a new instance of the TemperatureFragment
     *
     * @return The new instance of the TemperatureFragment
     */
    public static TemperatureFragment newInstance() {
        return new TemperatureFragment();
    }

    /**
     * Method to create the view of the fragment
     *
     * @param inflater           The LayoutInflater object that can be used to inflate
     *                           any views in the fragment,
     * @param container          If non-null, this is the parent view that the fragment's
     *                           UI should be attached to.  The fragment should not add the view itself,
     *                           but this can be used to generate the LayoutParams of the view.
     * @param savedInstanceState If non-null, this fragment is being re-constructed
     *                           from a previous saved state as given here.
     * @return The view of the fragment
     */
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        // Call the ViewModelProvider to create a new instance of the TemperatureViewModel
        TemperatureViewModel temperatureViewModel =
                new ViewModelProvider(this).get(TemperatureViewModel.class);

        // Inflate the layout for this fragment
        binding = FragmentTemperatureBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        // Observe the LiveData from the TemperatureViewModel
        final TextView textView = binding.textTemperature;
        temperatureViewModel.getText().observe(getViewLifecycleOwner(), textView::setText);

        final TextView subtitleView = binding.chartLabel;
        temperatureViewModel.getSubtitle().observe(getViewLifecycleOwner(), subtitleView::setText);

        // Create the LineChart
        final LineChart lineChart = binding.chart;

        // Observe the LiveData from the TemperatureViewModel
        temperatureViewModel.getTemperature().observe(getViewLifecycleOwner(), temperature -> {
            // Create the entries for the LineChart by calling the createEntries method from the ChartUtils class
            List<Entry> entries = ChartUtils.createEntries(temperature, "created", "temperature");

            Log.d("TemperatureFragment", "Temperature entries created: " + entries);

            // Create the LineDataSet and LineData
            LineDataSet lineDataSet = new LineDataSet(entries, "Temperature");
            LineData lineData = new LineData(lineDataSet);
            // Set the LineData to the LineChart
            lineChart.setData(lineData);
            lineChart.invalidate();

            Log.d("TemperatureFragment", "Chart data set and invalidated");
        });

        // Button to refresh the temperature data
        binding.refreshButton.setBackgroundResource(R.drawable.cell_border);
        binding.refreshButton.setOnClickListener(v -> {
            try {
                temperatureViewModel.fetchTemperature();
            } catch (Exception e) {
                Log.e("TemperatureFragment", "Error fetching temperature data: " + e);
            }
        });

        // Return the view of the fragment
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