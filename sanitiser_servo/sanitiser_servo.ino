#include <Servo.h>

Servo myservo; 

int trig = 3; // attach pin 3 to Trig
int echo = 4; //attach pin 4 to Echo

int let;


void setup() {
  
myservo.attach(5);
pinMode(6, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}
void loop()
{
  //digitalWrite(vcc, HIGH);                    // establish variables for duration of the ping,and the distance result in inches and centimeters:
  long duration, inches, cm;                  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);                        // The same pin is used to read the signal from the PING))): a HIGH, pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);                 // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
  
  if ((cm < 10) && (let == 0)) {
   myservo.write(120);
   delay(1000);
   myservo.write(0);
    let = 1;
   delay(3000);
  }
  else if (cm >= 10)
  {
    
    let = 0;
  }
  else {
    myservo.write(0); //off
  }
}
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
