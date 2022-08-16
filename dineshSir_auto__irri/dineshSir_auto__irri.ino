void setup() {
 Serial.begin(9600);      // initializes serial communication at 9600 bits per second
  pinMode(5, OUTPUT); 
  pinMode(A1, INPUT);
  digitalWrite(5, LOW); 
  // sets pin for relay in output mode
}
void loop() {                        
  int sensorValue = analogRead(A1);    // read value of humidity sensor
  Serial.println(sensorValue);         // prints value to serial
  if(sensorValue > 700){               // checks if value is below treshold, treshold is set at 700, but should be costumized for your plants need
    digitalWrite(5, HIGH);             // turns relay on
    delay(1000);                       // waits for 1sec
  }
  else{
    digitalWrite(5, LOW);              // turns relay off
    delay(1000);                       // waits for 1sec
  }
}
