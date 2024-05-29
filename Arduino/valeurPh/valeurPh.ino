#include <Wire.h>            // Include the Wire library for I2C communication
#include <OneWire.h>         // Include the OneWire library for DS18B20 temperature sensor
#include <DallasTemperature.h> // Include the DallasTemperature library for DS18B20 temperature sensor

#define lightDetectorPin A0  // Light detector pin
#define temperatureSensorPin 2 // DS18B20 temperature sensor pin
#define phMeterPin A1        // PH meter pin

OneWire oneWire(temperatureSensorPin); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);   // Pass the oneWire reference to Dallas Temperature sensor 

void setup() {
  pinMode(lightDetectorPin, INPUT); // Set light detector pin as input
  pinMode(13, OUTPUT);              // Set LED pin as output
  Serial.begin(9600);               // Start serial communication
  
  Wire.begin();                     // Initialize I2C communication for the magnetometer
  sensors.begin();                  // Start DS18B20 temperature sensor
}

void loop() {
  // Light sensor
  int lightValue = analogRead(lightDetectorPin); // Read light sensor value
  Serial.print("Light Sensor: ");                // Print light sensor value
  Serial.println(lightValue);

  // Magnetometer (PmodCMP2)
  // Add your magnetometer code here

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

  digitalWrite(13, HIGH); // Turn on LED
  delay(800);
  digitalWrite(13, LOW);  // Turn off LED
}