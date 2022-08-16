

char BluetoothData; // the Bluetooth data received

void setup() {

  Serial.begin(9600);


  //Set Digital Pins 4 to 7 as Output
  
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //pinMode(9, OUTPUT);
  //pinMode(10, OUTPUT);
 

  //Set State of Pins all to LOW (0)
  
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  //digitalWrite(9, 0);
  //digitalWrite(10, 0);
  
}
void loop() {

  if (Serial.available()) {

    BluetoothData = Serial.read(); //Get next character from bluetooth

    if (BluetoothData == 'V') {
      digitalWrite(8, 1);
      
    }
    if (BluetoothData == 'v') {
      digitalWrite(8, 0);
    }
   /* if (BluetoothData == 'W') {
      digitalWrite(9, 1);
    }
    if (BluetoothData == 'w') {
      digitalWrite(9, 0);
    }
    if (BluetoothData == 'U') {
      digitalWrite(10, 1);
    }
    if (BluetoothData == 'u') {
      digitalWrite(10, 0);
    }*/
    if (BluetoothData == 'A') {
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
    }
    if (BluetoothData == 'B') {
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      digitalWrite(7, 0);
    }
    if (BluetoothData == 'C') {
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 1);
    }
     if (BluetoothData == 'S') {
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
    }
  
  }
  delay(10);// wait 10 ms

}
