#include "Ultrasonic.h"
Ultrasonic ultrasonic(9, 8); // Trig et Echo
 
void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop () {
  int dist = ultrasonic.Ranging(CM);
  Serial.print(dist);
  Serial.println(" cm");

  delay(100);
}