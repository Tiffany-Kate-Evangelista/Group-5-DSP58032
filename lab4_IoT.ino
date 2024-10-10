const int LEDS[] = {0, 4, 16, 17, 5, 18, 19, 21}; 

const int Motor_CW = 22; 

const int Motor_CCW = 23; 

const int Motor_EN = 14; 

 

int delayVal = 150; 

 

int controlstate = 0; 

 

#include "thingProperties.h" 

#include <WiFi.h> 

 

int controlState = 0; 

 

void setup() { 

  Serial.begin(9600); 

  delay(1500);  

  initProperties(); 

  ArduinoCloud.begin(ArduinoIoTPreferredConnection); 

  setDebugMessageLevel(2); 

  ArduinoCloud.printDebugInfo(); 

 

  for(int x = 0; x < 8; x++) { // Use < 8 instead of <= 7 

    pinMode(LEDS[x], OUTPUT); 

  } 

   

  pinMode(Motor_CW, OUTPUT); 

  pinMode(Motor_CCW, OUTPUT); 

  pinMode(Motor_EN, OUTPUT); // Ensure Motor_EN is also set 

} 

 

void loop() { 

  ArduinoCloud.update(); 

 

  controlState = (controlState + 1) % 4; // Increment state each loop 

 

    switch (controlState) { 

    case 0b00: 

        onLEDLRChange(); 

        break; 

    case 0b01: 

        onLEDRLChange(); 

        break; 

    case 0b10: 

        onMotorCCWChange(); 

        break; 

    case 0b11: 

        onMotorCWChange(); 

        break; 

    default: 

        break; 

    } 

    delay(200); // Delay for a bit before the next loop iteration  

} 

 

void onLEDLRChange() { 

  if(lED_LR) { 

    for(int x = 0; x < 8; x++) { 

      digitalWrite(LEDS[x], HIGH); 

      delay(delayVal); 

    } 

    for(int x = 7; x >= 0; x--) { 

      digitalWrite(LEDS[x], HIGH); 

      delay(delayVal); 

      digitalWrite(LEDS[x], LOW); 

    } 

  } 

} 

 

void onLEDRLChange() { 

  if(lED_RL) { 

    for(int x = 7; x >= 0; x--) { 

      digitalWrite(LEDS[x], HIGH); 

      delay(delayVal); 

    } 

    for(int x = 0; x < 8; x++) { 

      digitalWrite(LEDS[x], HIGH); 

      delay(delayVal); 

      digitalWrite(LEDS[x], LOW); 

    } 

  } 

} 

 

void onMotorCCWChange() { 

  if(motor_CCW) { 

    digitalWrite(Motor_CCW, HIGH); 

    digitalWrite(Motor_CW, LOW); // Ensure the other motor is off 

    analogWrite(Motor_EN, 255);  

    delay(1000); 

    digitalWrite(Motor_CCW, LOW); 

    analogWrite(Motor_EN, 0);  

  } 

} 

 

void onMotorCWChange() { 

  if(motor_CW) { 

    digitalWrite(Motor_CW, HIGH); 

    digitalWrite(Motor_CCW, LOW); // Ensure the other motor is off 

    analogWrite(Motor_EN, 255);  

    delay(1000); 

    digitalWrite(Motor_CW, LOW); 

    analogWrite(Motor_EN, 0);  

  } 

} 