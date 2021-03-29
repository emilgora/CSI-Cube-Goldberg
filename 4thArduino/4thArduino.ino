// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int inputPin = 8;

const int stepsPerRevolution = 200;

void setup()
{
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(inputPin, INPUT_PULLUP);
}
void loop()
{
  // Set motor direction clockwise
  digitalWrite(dirPin, HIGH);

  // Set motor direction counterclockwise
  //digitalWrite(dirPin, LOW);

  int inputState = digitalRead(inputPin);

  if(inputState == LOW){
  // Spin motor quickly
    for(int x = 0; x < stepsPerRevolution; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }
  }
  else{
    digitalWrite(stepPin, LOW);
  }
}
