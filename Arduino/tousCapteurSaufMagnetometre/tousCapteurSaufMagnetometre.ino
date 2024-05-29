#include <Wire.h>  
#include <SoftwareSerial.h>             // Include the Wire library for I2C communication
#include <OneWire.h>            // Include the OneWire library for DS18B20 temperature sensor
#include <DallasTemperature.h>  // Include the DallasTemperature library for DS18B20 temperature sensor
#include <SPI.h>
#include <SD.h>                 // Include the SD library for writing to SD card
#include <ArduinoJson.h>        // Include the ArduinoJson library for JSON handling
#include <RTClib.h>



// #define lightDetectorPin A0     // Light detector pin
#define temperatureSensorPin 2   // DS18B20 temperature sensor pin
#define phMeterPin A1    
       // PH meter pin

#define SD_CS_PIN 4           // SD card chip select pin
#define lightPin 2              // Light detector pin
SoftwareSerial gsm(7, 8);                                                                // Définir les broches RX et TX du module GSM
File dataFile;    
String reponse;             // File object for data logging
RTC_DS3231 rtc; // Create an instance of the RTC object
OneWire oneWire(temperatureSensorPin); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);   // Pass the oneWire reference to Dallas Temperature sensor 
void setup() {
  
  // pinMode(lightDetectorPin, INPUT); // Set light detector pin as input
  Serial.begin(115200);
  delay(1000); // Wait for serial communication to initialize
  gsm.begin(115200);   
  sensors.begin();                  // Start DS18B20 temperature sensor
}

void loop() {
  delay(3000);

  // // getGPS();
  // return;
  // delay(10000);
  // Light sensor
  // int lightValue = analogRead(lightDetectorPin); // Read light sensor value
  // Serial.print("Light Sensor: ");                // Print light sensor value
  // Serial.println(lightValue);
  // Temperature sensor (DS18B20)
  sensors.requestTemperatures();     // Request temperature from DS18B20 sensor
  float temperature_raw = sensors.getTempCByIndex(0); // Read temperature in Celsius
  float temperature = round(temperature_raw * 100.0) / 100.0; // Limit to two decimal places
  Serial.print("Temperature: ");     // Print temperature
  Serial.print(temperature);
  Serial.println(" °C");

  // pH meter
  unsigned long int avgValue;
  float b;
  int buf[10],temp;
 
  for(int i=0;i<10;i++) { 
    buf[i]=analogRead(phMeterPin);
    delay(10);
  }
  for(int i=0;i<9;i++) {
    for(int j=i+1;j<10;j++) {
      if(buf[i]>buf[j]) {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++) {
    avgValue+=buf[i];
  }
  float phValue=(float)avgValue*5.0/1024/6; 
  phValue=0.6+3.5*phValue;                   
  Serial.print("pH:");  
  Serial.print(phValue, 2);
  Serial.println(" ");

  String jsonDataTemperature = "{\"temperature\":" + String(temperature) + "}";  // Construire la chaîne JSON avec la température
  String jsonDataAcidite = "{\"pH\":" + String(phValue) + "}"; 

  // String urlTemperatureStr = String(urlTemperature);
  // String urlAciditeStr = String(urlAcidite);
  Serial.print("Le Url:  ");
  sendDataTemp(jsonDataTemperature); 

  delay(5000);  

  sendDataPh(jsonDataAcidite);


  delay(30000);  



}
float getTemperature() {
  sensors.requestTemperatures();     // Request temperature from DS18B20 sensor
  return sensors.getTempCByIndex(0); // Read temperature in Celsius
}

float getpH() {
  unsigned long int avgValue;
  int buf[10],temp;
 
  for(int i=0;i<10;i++) { 
    buf[i]=analogRead(phMeterPin);
    delay(10);
  }
  for(int i=0;i<9;i++) {
    for(int j=i+1;j<10;j++) {
      if(buf[i]>buf[j]) {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++) {
    avgValue+=buf[i];
  }
  float phValue=(float)avgValue*5.0/1024/6; 
  return 0.6+3.5*phValue;                   
}

String getTime() {
  DateTime now = rtc.now(); // Get the current date and time from the RTC
  return now.timestamp();   // Return the timestamp as a string
}
void readFile(const char* filename) {
  File dataFile = SD.open(filename);
  if (dataFile) {
    Serial.println("File content:");
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  } else {
    Serial.println("Error opening file!");
  }
}

void getGPS() {
  // gsm.println("AT+CGNSSMODE=15,1");
  // delay(3000);
  // gsm.println("AT+CGPSNMEA=200191");
  // delay(3000);

  gsm.println("AT+CGPS=1"); 
 // Je démarre le GPS
  delay(2000);

  gsm.println("AT+CGPSINFO");  // Je demande les infos
  delay(1000);

  while (gsm.available()) {
    char c = gsm.read();
    Serial.print(c);
    reponse += c;
  }
  //   // Find and extract latitude and longitude from GPS information
  // int latIndex = reponse.indexOf(","); // Find index of first comma
  // int longIndex = reponse.indexOf(",", latIndex + 1); // Find index of second comma

  // String latitude = reponse.substring(latIndex + 1, longIndex); // Extract latitude
  // String longitude = reponse.substring(longIndex + 1); // Extract longitude
  // delay(1000);
  // // Print latitude and longitude
  // Serial.print("Latitude: ");
  // Serial.println(latitude);
  // delay(1000);

  // Serial.print("Longitude: ");
  // Serial.println(longitude);

  // String gpsInfo = reponse.substring(reponse.length() - 17);  // Je récupère les derniers caractères
  // Serial.print("Informations de localisation:");
  Serial.println(reponse);
  gsm.println("AT+CGPS=0");  // Je shut down le GPS
}
bool isGSMConnected() {
  Serial.println("Checking GSM connection...");
  gsm.println("AT"); // Send AT command to GSM module
  delay(1000); // Wait for response

  String response = ""; // Initialize an empty string to store the response

  while (gsm.available()) {
    char c = gsm.read(); // Read character from GSM module
    response += c; // Append character to the response string
    Serial.print(c); // Print the received character
    
    // Check if the response contains "OK"
    if (response.indexOf("OK") != -1) {
      Serial.println(" - OK received!"); // Debug statement
      return true; // GSM module is connected
    }
  }

  Serial.println(" - No OK received!"); // Debug statement
  return false; // GSM module is not connected
}



void sendDataTemp(String jsonData) {


  Serial.println("Sending HTTP request...");

  gsm.println("AT+HTTPTERM");
  delay(5000);

  gsm.println("AT+HTTPINIT");
  delay(5000);
  Serial.println("HTTP initialized ...");
  gsm.print("AT+HTTPPARA=\"URL\",\"");
  gsm.print("http://julien.lamy.mobi:4000/api/capteurs/capteur_temperature");
  gsm.println("\"");
  delay(5000);
  
  

  gsm.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(5000);

  Serial.print("Data length sent: ");
  Serial.println(jsonData.length());
  gsm.print("AT+HTTPDATA=");
  gsm.print(jsonData.length());
  gsm.println(",5000");
  delay(5000);
 
  Serial.print("Data sent: ");
  Serial.println(jsonData);
  gsm.println(jsonData);
  delay(5000);

  gsm.println("AT+HTTPACTION=1");
  delay(5000);

  Serial.println("HTTP request sent.");

  gsm.println("AT+HTTPTERM");
  delay(5000);
}
void sendDataPh(String jsonData) {


  Serial.println("Sending HTTP request...");

  gsm.println("AT+HTTPTERM");
  delay(5000);

  gsm.println("AT+HTTPINIT");
  delay(5000);
  Serial.println("HTTP initialized ...");
  gsm.print("AT+HTTPPARA=\"URL\",\"");
  gsm.print("http://julien.lamy.mobi:4000/api/capteurs/capteur_acidite");
  gsm.println("\"");
  delay(5000);
  
  

  gsm.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(5000);

  Serial.print("Data length sent: ");
  Serial.println(jsonData.length());
  gsm.print("AT+HTTPDATA=");
  gsm.print(jsonData.length());
  gsm.println(",5000");
  delay(5000);
 
  Serial.print("Data sent: ");
  Serial.println(jsonData);
  gsm.println(jsonData);
  delay(5000);
  Serial.print("Data sent: ");
  Serial.println(jsonData);

  gsm.println("AT+HTTPACTION=1");
  delay(5000);

  Serial.println("HTTP request sent.");

  gsm.println("AT+HTTPTERM");
  delay(5000);
}


