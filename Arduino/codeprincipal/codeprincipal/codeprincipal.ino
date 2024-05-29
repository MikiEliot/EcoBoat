#include "BTHC05.h"
#include "Ultrasonic.h"
#include <Servo.h>

// Deux moteurs DC, un servo moteur sur le quel est posé le capteur de distance. Un module BTHC (bluetooth)
// Connexion Servo : fil rouge au milieu a 5v, fil marron a ground (GND) et fil orange a pin 13
// Connexion Capteur de distance HC-SR04 : VCC a 5v, GND a GND, Trig a pin 9, Echo a pin 8
// Connexion moteurs par module L293D : motor1-1 a pin 2, motor1-2 a pin3
// motor 2-1 pin 4, motor 2-2 pin 7, enable1pin a pin 5, enable2pin a pin 6
// les deux coté de L293D sont connecter a 5v et a GND chaqun de son partie de breadboard
int servoPin = 13; 
Servo Servo1; 
Ultrasonic ultrasonic(9, 8); // Trig et Echo

BTHC05 bthc05(10, 11); // TXD to pin 10, RXD to pin 11 (adjust pins based on your connections)
int motor1Pin1 = 2; // pin 2 on L293D IC
int motor1Pin2 = 3; // pin 7 on L293D IC
int enable1Pin = 5; // pin 1 on L293D IC
int motor2Pin1 = 4; // pin 10 on L293D IC
int motor2Pin2 = 7; // pin 15 on L293D IC
int enable2Pin = 6; // pin 9 on L293D IC
int state;
int flag=0;        //makes sure that the serial only prints once the state
int stateStop=0;
bool moveServoFlag = true;
void setup() {
    // Servo1.attach(servoPin);
    // sets the pins as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    // sets enable1Pin and enable2Pin high so that motor can turn on:
    digitalWrite(enable1Pin, HIGH);
    digitalWrite(enable2Pin, HIGH);
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    bthc05.begin(9600);

    Serial.println("Bluetooth On....");
}
// ----------------------------------------- Modified code with bluetooth -------------------------------------------------
void loop() {
    // int dist = ultrasonic.Ranging(CM);
    // Serial.print(dist);
    // Serial.println(" cm");

    delay(500);
    if (bthc05.available()) {
        char command = bthc05.read();

        // Process Bluetooth command
        switch (command) {
            case 'F':
                moveForward();
                break;
            case 'R':
                turnLeft();
                break;
            case 'S':
                stopMotors();
                break;
            case 'L':
                turnRight();
                break;
            case 'B':
                reverse();
                break;
            default:
                // Handle unknown command
                break;
        }
    }
    // Pour utilisé le capter de la distance, il faut decommenter cette partie du code
    // else {
    //     moveServo();
    //     if (dist < 100) {
    //         stopMotors();
    //     } else {
    //         moveForward();
    //     }
    // }
}
    


void moveServo() {
  static unsigned long prevMillis = 0;
  static int step = 0;
  const int totalSteps = 3;
  const int duration = 2; // 20 seconds

  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= duration / totalSteps) {
    prevMillis = currentMillis;
    int angle = map(step, 0, totalSteps, 0, 90);
    Servo1.write(angle);

    step++;
    if (step >= totalSteps) {
      step = 0;
      delay(500); // Wait for 1 second before reversing
    }
  }
}


void moveForward() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    Serial.println("Go Forward!");
}

void turnLeft() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("Turn LEFT");
    // delay(1500);
    // stopMotors();
}

void stopMotors() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("STOP!");
}

void turnRight() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    Serial.println("Turn RIGHT");
    // delay(1500);
    // stopMotors();
}

void reverse() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("Reverse!");
}


