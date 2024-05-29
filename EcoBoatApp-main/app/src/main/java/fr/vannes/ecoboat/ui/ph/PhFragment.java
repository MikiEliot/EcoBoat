package fr.vannes.ecoboat.ui.ph;

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
import fr.vannes.ecoboat.databinding.FragmentPhBinding;
import fr.vannes.ecoboat.utils.ChartUtils;

public class PhFragment extends Fragment {

    // The binding for the fragment
    private FragmentPhBinding binding;

    /**
     * Method to create a new instance of the PhFragment
     *
     * @return The new instance of the PhFragment
     */
    public static PhFragment newInstance() {
        return new PhFragment();
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
        // Call the ViewModelProvider to create a new instance of the PhViewModel
        PhViewModel phViewModel =
                new ViewModelProvider(this).get(PhViewModel.class);

        // Inflate the layout for this fragment
        binding = FragmentPhBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        // Observe the LiveData from the PhViewModel
        final TextView textView = binding.textPh;
        phViewModel.getText().observe(getViewLifecycleOwner(), textView::setText);

        final TextView subtitleView = binding.chartLabel;
        phViewModel.getSubtitle().observe(getViewLifecycleOwner(), subtitleView::setText);

        // Create the LineChart
        final LineChart lineChart = binding.chart;

        // Observe the LiveData from the PhViewModel
        phViewModel.getPh().observe(getViewLifecycleOwner(), ph -> {
            // Create the entries for the LineChart by calling the createEntries method from the ChartUtils class
            List<Entry> entries = ChartUtils.createEntries(ph, "created", "pH");

            Log.d("TemperatureFragment", "Temperature entries created: " + entries);

            // Create the LineDataSet and LineData
            LineDataSet lineDataSet = new LineDataSet(entries, "pH");
            LineData lineData = new LineData(lineDataSet);
            // Set the LineData to the LineChart
            lineChart.setData(lineData);
            lineChart.invalidate();

            Log.d("TemperatureFragment", "Chart data set and invalidated");
        });

        // Button to fefresh the temperature data
        binding.refreshButton.setBackgroundResource(R.drawable.cell_border);
        binding.refreshButton.setOnClickListener(v -> {
            try {
                phViewModel.fetchPh();
            } catch (Exception e) {
                Log.e("PhFragment", "Error fetching pH data: " + e);
            }
        });


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