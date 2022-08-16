#include <SoftwareSerial.h>

char incoming_char=0;
int state = 0;
const int pin = 9;
float latitude,longitude;
// The TinyGPS++ object
//TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial SIM900(2, 3); 
void setup()
{
  Serial.begin(9600);
  //ss.begin(GPSBaud);
    SIM900.begin(9600);
  pinMode(pin, INPUT);
delay(20000); 

//SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  
  
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  /*while (Serial.available() > 0)
      {
        if (gps.encode(Serial.read()))
        {
        if (gps.location.isValid())
        {
          latitude =  gps.location.lat();
          longitude = gps.location.lng();
        }
        }
       
        
      }*/
      
  SIM900.print("AT+CNMI=2,2,0,0,0");   
    //Get the character from the cellular serial port
     String buffer = SIM900.readString();

    if (buffer.startsWith("\r\n+CMT: "))
    {
        
        
        // Remove first 51 characters
        buffer.remove(0, 51);
        int len = buffer.length();
        // Remove \r\n from tail
        buffer.remove(len - 2, 2);
        
        Serial.println(buffer);
    }
    
}
    
