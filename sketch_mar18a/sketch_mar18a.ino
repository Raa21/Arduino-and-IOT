#include <NewPing.h>
#include <Servo.h>

Servo myservo; 

#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). 
                         //Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN); // NewPing setup of pins and maximum distance.
int buzzerPin = 10;
int redLEDPin = 13;
int yellowLEDPin = 9;




int pos = 0; 
// SETUP *******************************************************************
void setup() 
{
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);


myservo.attach(11); 
}
// LOOP **********************************************************************
void loop()
{ 
int chooseLED;
 unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  int value = ((uS / US_ROUNDTRIP_CM) * 0.3937);
Serial.println(value);

if (value >0 && value <60 )

{ 
  int pos =20; 
  myservo.write(pos);  
   
  digitalWrite(redLEDPin,HIGH);
  
  }
  else if (value >= 60  ){

    int pos = 160; 
 myservo.write(pos);      
  digitalWrite(redLEDPin,!HIGH);
  }

delay(1000);
}


// GETDISTANCE *******************************************************************

