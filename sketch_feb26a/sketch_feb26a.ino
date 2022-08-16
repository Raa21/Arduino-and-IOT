int pushButton = 3;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  //pinMode(7, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  if ( buttonState == 0)
  {
    digitalWrite(6, HIGH);
   // digitalWrite(7, HIGH);
    digitalWrite(5, LOW);
  }
  else
  {
   digitalWrite(6, LOW);
   // digitalWrite(7, LOW);
    digitalWrite(5, HIGH); 
  }
  delay(1000);        // delay in between reads for stability
}
