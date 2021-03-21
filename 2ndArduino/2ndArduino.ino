#include "Adafruit_TCS34725.h"
#include <Wire.h>

// Adafruit color sensor library constructor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
byte gammatable[256]; 

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print("Red value: "); Serial.println(r, DEC);  // Outputs red color value to Serial monitor

    if(r > 4100) {
    digitalWrite(A1, LOW);
  }
  else{
    digitalWrite(A1, HIGH);
  }

}
