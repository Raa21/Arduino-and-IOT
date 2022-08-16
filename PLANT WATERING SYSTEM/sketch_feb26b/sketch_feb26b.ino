void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  if(sensorValue > 750)
  {
    digitalWrite(6, LOW);
  }
  else
  {
    digitalWrite(6, HIGH);
  }
  delay(1000);        // delay in between reads for stability
}
