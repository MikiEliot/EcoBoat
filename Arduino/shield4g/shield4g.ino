#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
#define baudrate 38400

String msg;

SoftwareSerial hc05(rxPin, txPin);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("ENTER AT Commands:");

  hc05.begin(baudrate);  // Set the baud rate for SoftwareSerial
  hc05.setTimeout(100);  // Set a timeout for reading from the HC-05 module
}

void loop() {
  readSerialPort();
  if (msg != "") {
    hc05.println(msg);  // Send command to HC-05 module
    delay(100);          // Wait for response (adjust as needed)
    
    // Read and print the response from the HC-05 module
    while (hc05.available() > 0) {
      char c = hc05.read();
      Serial.print(c);
  }
}}

void readSerialPort() {
  msg = "";
  while (Serial.available()) {
    delay(10);
    if (Serial.available() > 0) {
      char c = Serial.read();  // gets one byte from serial buffer
      msg += c;               // makes the string readString
    }
  }
}