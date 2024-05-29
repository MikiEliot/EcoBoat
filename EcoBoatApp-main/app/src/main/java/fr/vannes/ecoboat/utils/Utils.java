package fr.vannes.ecoboat.utils;

/**
 * Utility class
 */
public class Utils {
    
    /**
     * Calculate the water quality
     * @param temperature the temperature
     * @param pH the pH
     * @param nitrates the nitrates
     * @return the water quality
     */
    public static int calculateWaterQuality(double temperature, double pH, double nitrates) {
        double penalty = 0;

        // Temperature normalisation
        double T;
        if (temperature >= 8 && temperature <= 18) {
            T = 1;
        } else if (temperature < 8) {
            T = Math.max(0, 1 - Math.pow((8 - temperature) / 8, 2));
            penalty += 0.1 * ((8 - temperature) / 8);
        } else {
            T = Math.max(0, 1 - Math.pow((temperature - 18) / 12, 2));
            penalty += 0.1 * ((temperature - 18) / 12);
        }

        // pH normalisation
        double P = 1 - Math.pow((pH - 7) / 7, 2);
        if (pH < 6 || pH > 8) {
            penalty += 0.1 * (Math.abs(pH - 7) / 7);
        }

        // Nitrate normalisation
        double N;
        if (nitrates <= 10) {
            N = (20 - nitrates) / 20;
        } else {
            N = Math.max(0, 1 - Math.pow((nitrates - 10) / 20, 2));
            penalty += 0.1 * ((nitrates - 10) / 20);
        }

        // Calculating the water quality
        double waterQuality = ((T + P + N) / 3) * 100;

        // Penalizing the water quality
        waterQuality *= (1 - penalty);

        // Return the water quality to an integer
        return (int) Math.round(waterQuality);
    }
    
}
