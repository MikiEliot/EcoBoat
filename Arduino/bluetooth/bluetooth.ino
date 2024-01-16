// long duree;
// float dist;

// void setup(){
//   pinMode(7,OUTPUT);
//   pinMode(8,INPUT);
//   Serial.begin(9600);
// }

// void loop(){
//   digitalWrite(7,LOW);
//   delay(1000);

//   digitalWrite(7,HIGH);
//   delayMicroseconds(10);
//   digitalWrite(7,LOW);

//   duree = pulseIn(8,HIGH);
//   dist = (duree * 0.034) / 2;
//   Serial.println(dist);
// }


#include <SoftwareSerial.h>

SoftwareSerial BluetoothSerial(11,10);

void setup(){
  pinMode(11, INPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  BluetoothSerial.begin(9600);

}

void loop(){
  char var = 'z';
  if(BluetoothSerial.available()){
    var = (char) BluetoothSerial.read();
    if(var=='a'){
      Serial.println(var);
    }
  }
}

// #include <SoftwareSerial.h>
// #define rxPin 2
// #define txPin 3
// #define baudrate 38400

// String msg;

// SoftwareSerial hc05(rxPin, txPin);

// void setup() {
//   pinMode(rxPin, INPUT);
//   pinMode(txPin, OUTPUT);

//   Serial.begin(9600);
//   Serial.println("ENTER AT Commands:");
//   hc05.begin(baudrate);
// }

// void loop() {
//   readSerialPort();
//   if (msg != "") hc05.println(msg);

//   if (hc05.available() > 0) {
//     Serial.write(hc05.read());
//   }
// }

// void readSerialPort() {
//   msg = "";
//   while (Serial.available()) {
//     delay(10);
//     if (Serial.available() > 0) {
//       char c = Serial.read();  //gets one byte from serial buffer
//       msg += c;                //makes the string readString
//     }
//   }
// }