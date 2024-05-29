package fr.vannes.ecoboat.utils;

import fr.vannes.ecoboat.BuildConfig;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

import com.google.gson.Gson;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Utility class to manage the API.
 */
public class APIUtils {

    // API URL from the BuildConfig
    private static final String apiUrl = BuildConfig.API_URL;
    // API Username from the BuildConfig
    private static final String username = BuildConfig.API_USERNAME;
    // API Password from the BuildConfig
    private static final String password = BuildConfig.API_PASSWORD;
    // The token to access the API
    private String token;
    // The time the token was received
    private long tokenReceivedTime;
    // The OkHttpClient to make the requests
    private final OkHttpClient client;
    // The Gson object to parse the JSON
    private final Gson gson;

    /**
     * Constructor for the APIUtils
     */
    public APIUtils() {
        // Create the OkHttpClient
        client = new OkHttpClient();
        // The Gson object to parse the JSON
        gson = new Gson();
    }

    /**
     * Method to get the token to access the API
     *
     * @return The token
     * @throws IOException If the token cannot be retrieved
     */
    public String getToken() throws IOException {
        if (isTokenExpired()) {
            refreshToken();
        }
        return token;
    }

    /**
     * Method to get the data from the API
     *
     * @param url The URL to get the data from
     * @param keys The keys to get from the data
     * @return The data
     * @throws IOException If the data cannot be retrieved
     */
    public List<Map<String, String>> getData(String url, String... keys) throws IOException {
        String token = getToken();
        Request request = new Request.Builder()
                .url(apiUrl + url)
                .header("Authorization", "Bearer " + token)
                .build();

        try (Response response = client.newCall(request).execute()) {
            if (!response.isSuccessful()) {
                throw new IOException("Unexpected code " + response);
            }
            assert response.body() != null;
            String responseBody = response.body().string();

            Map<String, Object> map = gson.fromJson(responseBody, HashMap.class);
            if (map.containsKey("data")) {
                List<Map<String, Object>> dataList = (List<Map<String, Object>>) map.get("data");
                assert dataList != null;
                if (!dataList.isEmpty()) {
                    List<Map<String, String>> results = new ArrayList<>();
                    for (Map<String, Object> data : dataList) {
                        Map<String, String> result = new HashMap<>();
                        for (String key : keys) {
                            if (data.containsKey(key)) {
                                result.put(key, String.valueOf(data.get(key)));
                            }
                        }
                        if (!result.isEmpty()) {
                            results.add(result);
                        }
                    }
                    return results;
                } else {
                    throw new IOException("Data list is empty");
                }
            } else {
                throw new IOException("Data not found in response");
            }
        }
    }

    /**
     * Method to get the temperature data from the API
     *
     * @return The temperature data
     * @throws IOException If the temperature data cannot be retrieved
     */
    public List<Map<String, String>> getTemperature() throws IOException {
        return getData("/capteur_temperature/last", "temperature", "created");
    }

    /**
     * Method to get the pH data from the API
     *
     * @return The pH data
     * @throws IOException If the pH data cannot be retrieved
     */
    public List<Map<String, String>> getpH() throws IOException {
        return getData("/capteur_acidite/last", "pH", "created");
    }


    /**
     * Method to check if the token is expired
     *
     * @return True if the token is expired, false otherwise
     */
    private boolean isTokenExpired() {
        long currentTime = System.currentTimeMillis();
        long tokenAge = currentTime - tokenReceivedTime;
        return tokenAge >= 24 * 60 * 60 * 1000; // 24 hours in milliseconds
    }

    /**
     * Method to refresh the token if it is expired
     *
     * @throws IOException If the token cannot be refreshed
     */
    private void refreshToken() throws IOException {
        System.out.println("Refreshing token...");

        // Create the request body with the username and password
        Map<String, String> credentials = new HashMap<>();
        // Add the username and password to the map
        credentials.put("username", username);
        credentials.put("password", password);
        // Convert the map to JSON
        String jsonCredentials = gson.toJson(credentials);

        // Create the request body
        RequestBody body = RequestBody.create(
                jsonCredentials,
                MediaType.parse("application/json; charset=utf-8")
        );

        // Create the request
        Request request = new Request.Builder()
                .url(apiUrl + "/login")
                .post(body)
                .build();


        System.out.println("Sending request to " + apiUrl + "/login");

        // Send the request
        try (Response response = client.newCall(request).execute()) {
            // Check if the response is successful
            if (!response.isSuccessful()) {
                throw new IOException("Unexpected code " + response);
            }

            // Get the response body
            assert response.body() != null;
            String responseBody = response.body().string();

            // Print the response
            System.out.println("Received response: " + responseBody);

            // Parse the response
            Map<String, Object> map = gson.fromJson(responseBody, HashMap.class);
            if (map.containsKey("token")) {
                token = (String) map.get("token");
                tokenReceivedTime = System.currentTimeMillis();
                System.out.println("Token: " + token);
                System.out.println("Message: " + map.get("messsage")); // Print the message
                System.out.println("Data: " + map.get("data")); // Print the user data
            } else {
                throw new IOException("Token not found in response");
            }
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
            throw e;
        }
    }


}
