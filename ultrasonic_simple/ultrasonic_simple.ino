/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 Red POS to Arduino pin 11
 Green POS to Arduino pin 10
 560 ohm resistor to both LED NEG and GRD power rail
 More info at: http://goo.gl/kJ8Gl
 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */
/*#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);*/

const int trigPin = 4;
const int echoPin = 3;
long duration;
int distance, distanceInch;
/*#define led 9
#define led2 10
#define led3 11*/

void setup() {
  Serial.begin (9600);


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  
}

void loop() {
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
distanceInch = duration*0.0133/2;
Serial.println( distance );


  delay(1000);
}
