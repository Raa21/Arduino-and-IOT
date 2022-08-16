void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
   int sensorValue1 = analogRead(A1);
    int sensorValue2 = analogRead(A2);
  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print("      ");
  Serial.print(sensorValue1);
  Serial.print("      ");
  Serial.println(sensorValue2);
  
  if ( ((sensorValue > 329) && (sensorValue < 333)) && ((sensorValue1 > 329) && (sensorValue1 < 334)) && ((sensorValue2 > 394) && (sensorValue2 < 397)))
  {
    Serial.println("Everything OK!!");
  }
  if ( ((sensorValue > 328) && (sensorValue < 339)) && ((sensorValue1 > 345) && (sensorValue1 < 400)) && ((sensorValue2 > 345) && (sensorValue2 < 397)))
  {
    Serial.println("Front Accident!!");
  }
  if ( ((sensorValue > 328) && (sensorValue < 340)) && ((sensorValue1 > 265) && (sensorValue1 < 317)) && ((sensorValue2 > 339) && (sensorValue2 < 397)))
  {
    Serial.println("Back Accident!!");
  }
  if ( ((sensorValue > 340) && (sensorValue < 399)) && ((sensorValue1 >329 ) && (sensorValue1 < 334)) && ((sensorValue2 > 327) && (sensorValue2 < 395)))
  {
    Serial.println("Right Accident!!");
  }
  if ( ((sensorValue > 270 ) && (sensorValue < 317)) && ((sensorValue1 > 329) && (sensorValue1 < 334)) && ((sensorValue2 > 333) && (sensorValue2 < 397)))
  {
    Serial.println("Left Accident!!");
  }
  /*if ( ((sensorValue > 322) && (sensorValue < 328)) && ((sensorValue1 > 290) && (sensorValue1 < 350)) && ((sensorValue2 > 363) && (sensorValue2 < 390)))
  {
    Serial.println("Vechile Upsidedown !!");
  }*/
  
  delay(500);        // delay in between reads for stability
}
