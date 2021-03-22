#include "Arduino.h"
#include <AccelStepper.h>
#include <Servo.h>

// Inputs
const int entryPin = A4; //photocell
const int waterSensePin = A3;
const int preMagnetPin = A2; //photocell
const int colorPin = A1;

// Stepper aka fishing rod
#define FULLSTEP 4
AccelStepper myStepper(FULLSTEP, 9, 11, 10, 12);
int counter = 0;

// Outputs
const int solenoid1Pin = 5;
const int solenoid2Pin = 4;
const int magnetPin = 3;

// Exit ramp servo
#define servoPin 6
Servo exitServo;        

void setup() {
  
  Serial.begin(9600);
  
  pinMode(entryPin, INPUT_PULLUP); //photocell
  pinMode(waterSensePin, INPUT_PULLUP);
  pinMode(preMagnetPin, INPUT_PULLUP); //photocell
  pinMode(colorPin, INPUT_PULLUP);
  pinMode(solenoid1Pin, OUTPUT);
  pinMode(solenoid2Pin, OUTPUT);
  pinMode(magnetPin, OUTPUT);

  myStepper.setMaxSpeed(1000);
  myStepper.setSpeed(0);
  exitServo.attach(servoPin, 0, 10000);  
  
}

void loop() {
  
  int entryState = digitalRead(entryPin); //photocell
  int waterState = digitalRead(waterSensePin);
  int preMagnetState = digitalRead(preMagnetPin); //photocell
  int colorState = digitalRead(colorPin);
  Serial.print("entry:"); Serial.print(entryState); 
  Serial.print("preMag:"); Serial.println(preMagnetState);
  
  // Step 1

  if(entryState == LOW) { // photocell tuning here
    delay(3000);
    digitalWrite(solenoid1Pin, HIGH);
    delay(5000);
    digitalWrite(solenoid1Pin, LOW);
    delay(1000);
    digitalWrite(solenoid1Pin, HIGH);
    delay(1000);
    digitalWrite(solenoid1Pin, LOW);
  }
  else {
     digitalWrite(solenoid1Pin, LOW);
  }
  
  // Step 2
  
  if(waterState == LOW) {
    delay(1000);
    digitalWrite(solenoid2Pin, HIGH);
    delay(1000);
    digitalWrite(solenoid2Pin, LOW);
    delay(1000);
    digitalWrite(solenoid2Pin, HIGH);
    delay(1000);
    digitalWrite(solenoid2Pin, LOW);
    delay(1000);
    digitalWrite(solenoid2Pin, HIGH);
    delay(1000);
    digitalWrite(solenoid2Pin, LOW);
  }
  else {
    digitalWrite(solenoid2Pin, LOW);
  }
  
  // Step 3

  myStepper.runSpeed();
  
  if(preMagnetState == LOW && counter == 0) { //photocell tuning here
    digitalWrite(magnetPin, 255);
    delay(3000); 
    myStepper.setSpeed(-500); 
  }

  // Step 4

  if(colorState == LOW) {
    counter = 1;
    myStepper.setSpeed(0); 
    exitServo.write(180);
    delay(3000);
    digitalWrite(magnetPin, 0);
    delay(15000);
  }
  else{
    exitServo.write(0);
  }

}
