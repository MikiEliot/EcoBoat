#include <BTHC05.h>

 //all pins must be PWM enabled pin with ~ printed beside them


#include "BTHC05.h"
BTHC05 bthc05(10, 11); // RXD to pin 10, TXD to pin 11 (adjust pins based on your connections)

const int D0=9;
const int D1=6;
const int D2=5;
const int D3=3;

bool CW = true;
bool CCW = false;


bool debug = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Robojax TA6586 Motor Control");
  bthc05.begin(9600);
  Serial.println("Bluetooth On....");

 pinMode(D0, OUTPUT);
 pinMode(D1, OUTPUT);
 pinMode(D2, OUTPUT);
 pinMode(D3, OUTPUT);  
 
 
}

void loop() {
  // * Full video details: https://youtu.be/W_Wm28nQAYA
   if (bthc05.available()) {
         Serial.println("Bluetooth module available");
        char command = bthc05.read();
        Serial.print("Received command: ");
        Serial.println(command);
        switch (command) {
            case 'F':
            //move forward
                M1(CCW, 90);
                M2(CCW,90);
                break;
            case 'R':
            //move right
                M1(CCW, 90);
                M2(CCW,0);
                break;
            case 'S':
            //stop
                fullBrake();
                break;
            case 'L':
            //move left
                M1(CCW, 0);
                M2(CCW,90);
                break;
            case 'B':
                M1(CW, 90);
                M2(CW,90);
                break;
            default:
            //move forward at 50%
                // M1(CCW, 50);
                // M2(CCW,50);
                break;
        }
    }
}
/*
 *  M1(bool direction,int speed)
 * @brief runs motor 1 
 * @param direction is CW or CCW, 
 * @param speed is integer between 0 to 100

 * @return returns non
 * Written by Ahmad Shamshiri for robojax.com
 * on Mar 22, 2022 
 * Full video details: https://youtu.be/W_Wm28nQAYA
 */
void M1(bool direction,int speed)
{
  int pwm=map(speed, 0, 100, 0, 255);
  if(direction == CW)
  {
   analogWrite(D0,pwm);
   analogWrite(D1,LOW);   
  }else{
   analogWrite(D1,pwm);
   analogWrite(D0,LOW);     
  }
  debugPrint(1, direction, speed, false); 
}//M1 end


void printMotorStatus(const char* message, void (*motorFunction)(bool, int)) {
  Serial.print(message);
  motorFunction(CW, 0); // Call the motor function with dummy values for direction and speed
  Serial.println();
}

/*
 *  M2(bool direction,int speed)
 * @brief runs motor 2 
 * @param direction is CW or CCW, 
 * @param speed is integer between 0 to 100

 * @return returns non
 * Written by Ahmad Shamshiri for robojax.com
 * on Mar 22, 2022 
 * Full video details: https://youtu.be/W_Wm28nQAYA
 */
void M2(bool direction,int speed)
{
  int pwm=map(speed, 0, 100, 0, 255);
  if(direction == CW)
  {
   analogWrite(D2,pwm);
   analogWrite(D3,LOW);   
  }else{
   analogWrite(D3,pwm);
   analogWrite(D2,LOW);     
  } 
  debugPrint(2, direction, speed, false);    
}//M2 ends


/*
 *  brake(int motor)
 * @brief applies brake to a motor
 * @param "motor" is integer 1 or 2

 * @return returns none
 * Written by Ahmad Shamshiri for robojax.com
 * on Mar 22, 2022 
 * Full video details: https://youtu.be/W_Wm28nQAYA
 */
void brake(int motor)
{
   if(motor == 1)
  {
   analogWrite(D0,HIGH);
   analogWrite(D1,HIGH);   
  }else{
   analogWrite(D2,HIGH);
   analogWrite(D3,HIGH);     
  }
  debugPrint(motor, true,  0, true);  
}//brake ends


/*
 * debugPrint(int motor, bool direction, int speed, bool stop)
 * @brief prints debugging information
 * @param "motor" is integer 1 or 2
 * @param "direction" is CW or CCW
 * @param "speed" is 0 to 100
 * @param "stop" is true or false, if true, the word "stop" is printed

 * @return returns none
 * Written by Ahmad Shamshiri for robojax.com
 * on Mar 22, 2022 
 * Full video details: https://youtu.be/W_Wm28nQAYA
 */
void debugPrint(int motor, bool direction, int speed, bool stop) {
   if (debug) {
      Serial.print("Motor: ");
      Serial.print(motor);
      if (stop && motor > 0) {
         Serial.println(" Stopped");
      } else {
         Serial.print(direction ? " CW" : " CCW");
         if (!stop) {
            Serial.print(" at ");
            Serial.print(speed);
            Serial.print("%");
         }
         Serial.println();
      }
   }
}

//not used but can be used to apply brake on both motors
void fullBrake()
{
 brake(1);
 brake(2); 

}