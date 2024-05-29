// #include "Ultrasonic.h"

// #define RELAY_PIN 3  // Pin connected to the relay module control (IN1)
// #define RELAY_ON HIGH
// #define RELAY_OFF LOW

// // HC-SR04 pins
// const int echoPins[] = {12, 9, 6};  // Echo pins for each sensor
// const int trigPins[] = {13, 10, 7}; // Trigger pins for each sensor

// const int trigPin1 = 13; 
// const int echoPin1 = 12;

// const int trigPin2 = 10; 
// const int echoPin2 = 9;

// const int trigPin3 = 7; 
// const int echoPin3 = 6;

// // Create an array of Ultrasonic objects for each sensor
// Ultrasonic ultrasonic[] = {
//   Ultrasonic(trigPins[0], echoPins[0]),
//   Ultrasonic(trigPins[1], echoPins[1]),
//   Ultrasonic(trigPins[2], echoPins[2])
// };

// void setup() {
//   pinMode(RELAY_PIN, OUTPUT);
//   digitalWrite(RELAY_PIN, RELAY_OFF); // Ensure relay is initially off

//   pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output 
//   pinMode(echoPin1, INPUT); // Sets the echoPin as an Input 
//   pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output 
//   pinMode(echoPin2, INPUT); // Sets the echoPin as an Input 
//   pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output 
//   pinMode(echoPin3, INPUT); // Sets the echoPin as an Input 

// Serial.begin(9600); // Starts the serial communication

//   Serial.begin(9600);
// }

// void loop() {
//   int distances[3];  // Array to store distances from each sensor

//   // Read distances from each sensor
//   for (int i = 0; i < 3; i++) {
//     distances[i] = ultrasonic[i].Ranging(CM);
//     Serial.print("Distance from sensor ");
//     Serial.print(i + 1);
//     Serial.print(": ");
//     Serial.print(distances[i]);
//     Serial.println(" cm");
//     delay(5000);
//   }

//   // Check if any distance is smaller than 30 cm
//   for (int i = 0; i < 3; i++) {
//     if (distances[i] < 30) {
//       digitalWrite(RELAY_PIN, RELAY_ON); // Turn on relay (stop motor)
//       Serial.println("Distance below 30 cm. Motor stopped.");
//       return; // Exit loop if any distance is smaller than 30 cm
//     }
//   }

//   // If no distance is smaller than 30 cm, turn off relay
//   digitalWrite(RELAY_PIN, RELAY_OFF);
//   delay(100); // Adjust as needed for reliability
// }


#include "Ultrasonic.h"

#define RELAY_PIN 3  // Pin connected to the relay module control (IN1)
#define RELAY_ON HIGH
#define RELAY_OFF LOW

const int trigPin1 = 13; 
const int echoPin1 = 12;

const int trigPin2 = 10; 
const int echoPin2 = 9;

const int trigPin3 = 7; 
const int echoPin3 = 6;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF); // Ensure relay is initially off

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output 
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input 
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output 
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input 
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output 
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input 

  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  int distances[3];  // Array to store distances from each sensor

  // Read distances from each sensor
  distances[0] = getDistance(trigPin1, echoPin1);
  distances[1] = getDistance(trigPin2, echoPin2);
  distances[2] = getDistance(trigPin3, echoPin3);

  // Print distances
  for (int i = 0; i < 3; i++) {
    Serial.print("Distance from sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(distances[i]);
    Serial.println(" cm");
    delay(1000);
  }

  // Check if any distance is smaller than 30 cm
  for (int i = 0; i < 3; i++) {
    if (distances[i] > 0 && distances[i] < 20) {
      digitalWrite(RELAY_PIN, RELAY_OFF); // Turn on relay (stop motor)
      Serial.println("Distance below 30 cm. Motor stopped.");
      return; // Exit loop if any distance is smaller than 30 cm
    }
  }

  // If no distance is smaller than 30 cm, turn off relay
  digitalWrite(RELAY_PIN, RELAY_ON);
  delay(100); // Adjust as needed for reliability
}

// Function to get distance from ultrasonic sensor
int getDistance(int trigPin, int echoPin) {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Calculate distance in cm

  return distance;
}

