#include <Wire.h>  
#include <SoftwareSerial.h>             // Include the Wire library for I2C communication
#include <OneWire.h>            // Include the OneWire library for DS18B20 temperature sensor
#include <DallasTemperature.h>  // Include the DallasTemperature library for DS18B20 temperature sensor
#include <SPI.h>
#include <SD.h>                 // Include the SD library for writing to SD card
#include <ArduinoJson.h>        // Include the ArduinoJson library for JSON handling
#include <RTClib.h>



#define lightDetectorPin A0     // Light detector pin
#define temperatureSensorPin 2   // DS18B20 temperature sensor pin
#define phMeterPin A1    
       // PH meter pin

#define SD_CS_PIN 4           // SD card chip select pin
#define lightPin 2              // Light detector pin

SoftwareSerial gsm(7, 8);
String urlTemperature = "http://julien.lamy.mobi:4000/api/capteurs/capteur_temperature";  // Initialiser un variable avec l'url du capteur sur l'api
String urlAcidite = "http://julien.lamy.mobi:4000/api/capteurs/capteur_acidite";                                                                 // Définir les broches RX et TX du module GSM
File dataFile;    
String reponse;             // File object for data logging
RTC_DS3231 rtc; // Create an instance of the RTC object
OneWire oneWire(temperatureSensorPin); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);   // Pass the oneWire reference to Dallas Temperature sensor 

void setup() {
  pinMode(lightDetectorPin, INPUT); // Set light detector pin as input
  Serial.begin(115200);
  gsm.begin(115200);     // Initialiser le port série du module GSM
  Wire.begin();                     // Initialize I2C communication for the magnetometer
  sensors.begin();                  // Start DS18B20 temperature sensor
}

void loop() {
  // Light sensor
  int lightValue = analogRead(lightDetectorPin); // Read light sensor value
  Serial.print("Light Sensor: ");                // Print light sensor value
  Serial.println(lightValue);



  // Temperature sensor (DS18B20)
  sensors.requestTemperatures();     // Request temperature from DS18B20 sensor
  float temperature = sensors.getTempCByIndex(0); // Read temperature in Celsius
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
  getGPS();  // Une fois l'envoi terminé, appeler getGPS()

  sendDatas(jsonDataTemperature, urlTemperature); 
   // J'appelle la méthode sendDatas pour la température

  delay(3000);  // Attendre 1 minute avant la prochaine requête   


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

  gsm.println("AT+CGPS=1");  // Je démarre le GPS
  delay(2000);

  gsm.println("AT+CGPSINFO");  // Je demande les infos
  delay(1000);

  while (gsm.available()) {
    char c = gsm.read();
    reponse += c;
  }

  Serial.println(reponse);

  String gpsInfo = reponse.substring(reponse.length() - 17);  // Je récupère les derniers caractères
  Serial.print("Informations de localisation:");
  Serial.println(gpsInfo);
  gsm.println("AT+CGPS=0");  // Je shut down le GPS
}

void sendDatas(String jsonData, String url) {

  // Stop la requète HTTP en cours si il y en a une
  gsm.println("AT+HTTPTERM");
  delay(5000);

  // Initialise la requète HTTP
  gsm.println("AT+HTTPINIT");
  delay(5000);
  Serial.println("HTTP initialisé ...");

  gsm.print("AT+HTTPPARA=\"URL\",\"");  // On ajoute l'url dans le header
  gsm.print(url);
  gsm.println("\"");
  delay(5000);

  gsm.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");  // On spécifie le contenu
  delay(5000);

  gsm.print("AT+HTTPDATA=");     // J'utilise la commande AT+HTTPDATA pour passer les données des capteurs
  gsm.print(jsonData.length());  // Je dois lui donner la taille des données en bytes
  gsm.println(",5000");
  delay(5000);

  gsm.println(jsonData);  // Je passe les données
  delay(5000);

  gsm.println("AT+HTTPACTION=1");  // Appel de la méthode POST
  delay(5000);

  Serial.println("Requête HTTP envoyée.");

  gsm.println("AT+HTTPTERM");  // Fin de la requète
  delay(5000);
}