#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
//static const int RXPin = 4, TXPin = 5;
//static const uint32_t GPSBaud = 9600;
int state = 0;
const int pin = 9;
float latitude,longitude;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial SIM900(2, 3); 
void setup()
{
  Serial.begin(9600);
  //ss.begin(GPSBaud);
    SIM900.begin(19200);
  pinMode(pin, INPUT);
delay(20000); 
  /*Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();*/
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial.available() > 0)
      {
        if (gps.encode(Serial.read()))
        {
        if (gps.location.isValid())
        {
          latitude =  gps.location.lat();
          longitude = gps.location.lng();
        }
        }
       /* else
          {
            Serial.println(F("INVALID"));
          }*/
        
      }
          /*Serial.print(gps.location.lat(), 6);
          Serial.print(F(","));
          Serial.print(gps.location.lng(), 6);
          Serial.println();*/
            if (digitalRead(pin) == HIGH && state == 0) 
            {
              SIM900.print("AT+CMGF=1\r"); 
                delay(100);
              
                // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
                // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
                SIM900.println("AT+CMGS=\"+919078140061\""); 
                delay(100);
                
                // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
                SIM900.print("Latitude :"); 
                SIM900.println(latitude, 6);
                SIM900.print("Longitude :");
                SIM900.println(longitude, 6);
                delay(100);
              
                // End AT command with a ^Z, ASCII code 26
                SIM900.println((char)26); 
                delay(100);
                SIM900.println();
                // Give module time to send SMS
                
              /*Replace XXXXXXXXXX to 10 digit mobile number &
                ZZ to 2 digit country code*/
              
              
              //The text of the message to be sent.
              
             /* sgsm.print("https://www.google.com/maps/@");
              sgsm.print(latitude, 6);
              sgsm.print(',');
              sgsm.print(longitude, 6);
              sgsm.println(",14z");*/
               
              state = 1;
              delay(5000); 
    }
  if (digitalRead(pin) == LOW) 
  {
      state = 0;
    }
        
        
        
 }
    

 /* if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }*/

  
