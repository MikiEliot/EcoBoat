#include "BTHC05.h"
#include "Ultrasonic.h"






Ultrasonic ultrasonic(9, 8); // Trig et Echo

BTHC05 bthc05(10, 11); // RXD to pin 10, TXD to pin 11 (adjust pins based on your connections)
int motor1Pin1 = 2; // pin 2 on L293D IC
int motor1Pin2 = 3; // pin 7 on L293D IC
int enable1Pin = 5; // pin 1 on L293D IC
int motor2Pin1 = 4; // pin 10 on L293D IC
int motor2Pin2 = 7; // pin 15 on L293D IC
int enable2Pin = 6; // pin 9 on L293D IC
int state;
int flag=0;        //makes sure that the serial only prints once the state
int stateStop=0;
void setup() {
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

    // delay(500);
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
    // else if (!bthc05.available()) {
    //     if (dist < 100) {
    //         stopMotors();
    //     } else {
    //         moveForward();
    //     }
    // }
    // else {
    //   moveForward();
    // }
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
    // Serial.println("Turn LEFT");
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

