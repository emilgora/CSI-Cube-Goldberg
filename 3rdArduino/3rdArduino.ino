const int entryPin = A1; //photocell
const int preMagnetPin = A2; //photocell
const int entryOutput = 8;
const int preMagnetOutput = 9;


void setup() {
  Serial.begin(9600);
  
  pinMode(entryPin, INPUT); //photocell
  pinMode(preMagnetPin, INPUT); //photocell
  pinMode(entryOutput, OUTPUT);
  pinMode(preMagnetOutput, OUTPUT);
}

void loop() {
  int entryState = analogRead(entryPin); //photocell
  int preMagnetState = analogRead(preMagnetPin); //photocell

  Serial.print("entry:"); Serial.print(entryState); 
  Serial.print("preMag:"); Serial.println(preMagnetState);

  if (entryState < 950){
    digitalWrite(entryOutput, LOW);
  }
  else {
    digitalWrite(entryOutput, HIGH);
  }
  

  if (preMagnetState < 790){
    digitalWrite(preMagnetOutput, LOW);
  }
  else{
    digitalWrite(preMagnetOutput, HIGH);
  }
  delay(1);
}
