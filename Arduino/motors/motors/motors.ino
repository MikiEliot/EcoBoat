#include "BTHC05.h"

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

// void loop() {
//     //if some date is sent, reads it and saves in state
//     if(Serial.available() > 0){     
//       state = Serial.read();   
//       flag=0;
//     }   
//     // if the state is 'F' the DC motor will go forward
//     if (state == 'F') {
//         digitalWrite(motor1Pin1, HIGH);
//         digitalWrite(motor1Pin2, LOW); 
//         digitalWrite(motor2Pin1, LOW);
//         digitalWrite(motor2Pin2, HIGH);
//         if(flag == 0){
//           Serial.println("Go Forward!");
//           flag=1;
//         }
//     }
    
//     // if the state is 'R' the motor will turn left
//     else if (state == 'R') {
//         digitalWrite(motor1Pin1, HIGH); 
//         digitalWrite(motor1Pin2, LOW); 
//         digitalWrite(motor2Pin1, LOW);
//         digitalWrite(motor2Pin2, LOW);
//         if(flag == 0){
//           Serial.println("Turn LEFT");
//           flag=1;
//         }
//         delay(1500);
//         state=3;
//         stateStop=1;
//     }
//     // if the state is 'S' the motor will Stop
//     else if (state == 'S' || stateStop == 1) {
//         digitalWrite(motor1Pin1, LOW); 
//         digitalWrite(motor1Pin2, LOW); 
//         digitalWrite(motor2Pin1, LOW);
//         digitalWrite(motor2Pin2, LOW);
//         if(flag == 0){
//           Serial.println("STOP!");
//           flag=1;
//         }
//         stateStop=0;
//     }
//     // if the state is 'L' the motor will turn right
//     else if (state == 'L') {
//         digitalWrite(motor1Pin1, LOW); 
//         digitalWrite(motor1Pin2, LOW); 
//         digitalWrite(motor2Pin1, LOW);
//         digitalWrite(motor2Pin2, HIGH);
//         if(flag == 0){
//           Serial.println("Turn RIGHT");
//           flag=1;
//         }
//         delay(1500);
//         state=3;
//         stateStop=1;
//     }
//     // if the state is 'B' the motor will Reverse
//     else if (state == 'B') {
//         digitalWrite(motor1Pin1, LOW); 
//         digitalWrite(motor1Pin2, HIGH);
//         digitalWrite(motor2Pin1, HIGH);
//         digitalWrite(motor2Pin2, LOW);
//         if(flag == 0){
//           Serial.println("Reverse!");
//           flag=1;
//         }
//     }
    //For debugging purpose
    // Serial.println(state);

// ----------------------------------------- Modified code with bluetooth -------------------------------------------------
void loop() {
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
    delay(1500);
    stopMotors();
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
    delay(1500);
    stopMotors();
}

void reverse() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("Reverse!");
}

