#include<Wire.h>

#include "DHT.h"
#define DHTPIN 3
#define DHTTYPE DHT11
char BluetoothData; // the Bluetooth data received
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  //Set Digital Pins 4 to 7 as Output
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  //Set State of Pins all to LOW (0)
  digitalWrite(12, 0);
  digitalWrite(11, 0);
  digitalWrite(10, 0);
  digitalWrite(9, 0);
  digitalWrite(8, 0);
  digitalWrite(7, 0);
  digitalWrite(6, 0);

  
  
}
void loop()
{
  int h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 

  Serial.print("*T"+String(t)+"*");
  Serial.print("*H"+String(h)+"*");
 
  if (Serial.available()) {
    BluetoothData = Serial.read(); //Get next character from bluetooth
    if (BluetoothData == 'F') {
      digitalWrite(12, 1);
      digitalWrite(11, 0);
      digitalWrite(10, 1);
      digitalWrite(9, 0);
    }
    else if (BluetoothData == 'B') {
          digitalWrite(12, 0);
      digitalWrite(11, 1);
      digitalWrite(10, 0);
      digitalWrite(9, 1);
    }
    else if (BluetoothData == 'L') {
          digitalWrite(12, 1);
      digitalWrite(11, 0);
      digitalWrite(10, 0);
      digitalWrite(9, 1);
    }
    else if (BluetoothData == 'R') {
      digitalWrite(11, 1);
      digitalWrite(10, 1);
      digitalWrite(9, 0);
      digitalWrite(12, 0);
    }
    else if (BluetoothData == 'S') {
         digitalWrite(12, 0);
      digitalWrite(11, 0);
      digitalWrite(10, 0);
      digitalWrite(9, 0);
    }
    else if (BluetoothData == 'W') {
      digitalWrite(7, 1);

    }
    else if (BluetoothData == 'w') {
      digitalWrite(7, 0);
    }
   else if (BluetoothData == 'v') {
      digitalWrite(8, 1);
    }
    else if (BluetoothData == 'V') {
      digitalWrite(8, 0);
    }
    else if (BluetoothData == 'U') {
      digitalWrite(6, 1);
    }
    else if (BluetoothData == 'u') {
      digitalWrite(6, 0);
    }
  }
  delay(10);// wait 10 ms
}
