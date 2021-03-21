#include "Arduino.h"
#include <AccelStepper.h>
#include <Servo.h>

// Inputs
const int entryPin = 14;
const int waterSensePin = 15;
const int preMagnetPin = 16;

// Stepper aka fishing rod
#define FULLSTEP 4
AccelStepper myStepper(FULLSTEP, 9, 11, 10, 12);

// Outputs
const int solenoid1Pin = 3;
const int solenoid2Pin = 4;
const int magnetPin = 5;

// Exit ramp servo
#define servoPin 6
Servo exitServo;        

void setup() {
  
  Serial.begin(9600);
  
  pinMode(entryPin, INPUT_PULLUP);
  pinMode(waterSensePin, INPUT_PULLUP);
  pinMode(preMagnetPin, INPUT_PULLUP);
  pinMode(solenoid1Pin, OUTPUT);
  pinMode(solenoid2Pin, OUTPUT);
  pinMode(magnetPin, OUTPUT);

  myStepper.setMaxSpeed(1000);
  myStepper.setSpeed(0);
  exitServo.attach(servoPin, 0, 10000);  
  
}

void loop() {
  
  int waterState = digitalRead(waterSensePin);
  int entryState = digitalRead(entryPin);
  int preMagnetState = digitalRead(preMagnetPin);
  int colorState = digitalRead(5);
  
  // Step 1

  if(entryState == LOW) {
    delay(1000);
    digitalWrite(solenoid1Pin, HIGH);
    delay(5000);
  }
  else {
     digitalWrite(solenoid1Pin, LOW);
  }
  
  // Step 2
  
  if(waterState == LOW) {
    delay(1000);
    digitalWrite(solenoid2Pin, HIGH);
    delay(2000);
  }
  else {
    digitalWrite(solenoid2Pin, LOW);
  }
  
  // Step 3

  myStepper.runSpeed();
  
  if(preMagnetState == LOW) {
    digitalWrite(magnetPin, 255);
    delay(3000); 
    myStepper.setSpeed(-700); 
  }

  if(colorState > 4100) {
    myStepper.setSpeed(0); 
    delay(3000);
    digitalWrite(magnetPin, 0);
  }

  // Step 4

  if(waterState == LOW) {
    exitServo.write(0);
    delay(10000);
  }
  else {
    exitServo.write(180);
  }
  
}
