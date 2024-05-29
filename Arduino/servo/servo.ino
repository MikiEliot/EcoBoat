#include <Servo.h>


int servoPin = 13; 
Servo Servo1; 
void setup() {
  Servo1.attach(servoPin); // Attach the servo to the specified pin
  Serial.begin(9600);
}

void loop() {
  Serial.println("moving left ...");
  moveLeft();
  delay(3000);
  Serial.println("moving right ...");

  moveRight();
  delay(3000);
  }

void moveLeft() {
  static unsigned long prevMillis = 0;
  static int totalSteps = 45;
  static int duration = 15000; // 15 seconds
  static int startAngle = 0;
  static int targetAngle = 45;

  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= duration / totalSteps) {
    prevMillis = currentMillis;
    float t = float(currentMillis % (duration / totalSteps)) / (duration / totalSteps);
    int angle = startAngle + t * (targetAngle - startAngle);
    Servo1.write(angle);
  }
}

void moveRight() {
  static unsigned long prevMillis = 0;
  static int totalSteps = 45;
  static int duration = 15000; // 15 seconds
  static int startAngle = 45;
  static int targetAngle = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= duration / totalSteps) {
    prevMillis = currentMillis;
    float t = float(currentMillis % (duration / totalSteps)) / (duration / totalSteps);
    int angle = startAngle + t * (targetAngle - startAngle);
    Servo1.write(angle);
    if (currentMillis % duration == 0) {
      delay(1000); // Wait for 1 second before reversing
    }
  }
}