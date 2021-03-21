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

// Variables
int fooState = 0;
int barState = 0;
int counterX = 0;
int counterA = 0;
int counterB = 0;
int counterC = 0;
int entryState = HIGH;
int preMagnetState = HIGH;

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
  
  // Step 1

  int entryState = digitalRead(entryPin);

  if(entryState == LOW && counterX == 0) {
    delay(1000);
    digitalWrite(solenoid1Pin, HIGH);
    delay(5000);
    counterX+1;
  }
  else {
     digitalWrite(solenoid1Pin, LOW);
  }
  
  // Step 2
  
  if(waterState == LOW && counterA == 0) {
    delay(1000);
    digitalWrite(solenoid2Pin, HIGH);
    delay(2000);
    counterA+1;
  }
  else {
    digitalWrite(solenoid2Pin, LOW);
  }
  
  
  // Step 3

  int preMagnetState = digitalRead(preMagnetPin);

  myStepper.runSpeed();
  
  if(preMagnetState == LOW && counterC == 0) {
    analogWrite(magnetPin, 255);
    delay(1000); 
    myStepper.setSpeed(-500); 
    delay(1000);
    analogWrite(magnetPin, 190);
    Serial.println("hello");
  }

  /*
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print("Red value: "); Serial.println(r, DEC);  // Outputs red color value to Serial monitor

  
  if(r > 4100 && counterC == 0) {
    myStepper.setSpeed(0); 
    delay(2000);
    analogWrite(magnetPin, 0);
    counterC+1;
  }
  */

  // Step 4

  if(waterState == LOW) {
    exitServo.write(0);
    Serial.println("yep");
    delay(10000);
  }
  else {
    exitServo.write(180);
    Serial.println("nope");
  }
  
}
