package fr.vannes.ecoboat.utils;

import com.github.mikephil.charting.data.Entry;

import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;

/**
 * Utility class for the chart.
 */
public class ChartUtils {

    /**
     * Method to create entries for the chart
     * @param data The data to create the entries from
     * @param timestampKey The key for the timestamp
     * @param dataKey The key for the data
     * @return The entries for the chart
     */
    public static List<Entry> createEntries(List<Map<String, String>> data, String timestampKey, String dataKey) {
        List<Entry> entries = new ArrayList<>();
        for (Map<String, String> map : data) {
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                String dateString = Objects.requireNonNull(map.get(timestampKey));
                Instant instantCreated = Instant.parse(dateString);
                Instant instantNow = Instant.now();
                long differenceInSeconds = instantNow.getEpochSecond() - instantCreated.getEpochSecond();
                float differenceInMinutes = differenceInSeconds / 60.0f;
                float yValue = Float.parseFloat(Objects.requireNonNull(map.get(dataKey)));
                entries.add(new Entry(differenceInMinutes, yValue));
            }
        }
        return entries;
    }
}