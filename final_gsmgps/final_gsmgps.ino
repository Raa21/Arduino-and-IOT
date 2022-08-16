#include <TinyGPS++.h>
#include <SoftwareSerial.h>

char incoming_char=0;
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

SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  
  
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
       
        
      }
      
    if(SIM900.available() >0)
    {
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
        
      if( buffer == "Location" )
     {
      SIM900.println("AT+CMGS=\"+919078140061\""); 
                delay(100);
                
                // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
                SIM900.print("My Location:"); 
                 SIM900.print("https://www.google.com/maps/@");
                  SIM900.print(latitude, 6);
                  SIM900.print(',');
                  SIM900.print(longitude, 6);
                  SIM900.println(",14z");
                delay(100);
              
                // End AT command with a ^Z, ASCII code 26
                SIM900.println((char)26); 
                delay(100);
                SIM900.println();
     }
     else if(buffer == "On" )
     {
      digitalWrite(6, LOW);
     }
     else if(buffer == "Off" )
     {
      digitalWrite(6, HIGH);
     }
      else
      {
        Serial.println("Wrong Command");
      }
    }

    delay(100); 
    //Print the incoming character to the terminal
     
    }
          
          /*  if (digitalRead(pin) == HIGH && state == 0) 
            {
              SIM900.print("AT+CMGF=1\r"); 
                delay(100);
              
                // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
                // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
                SIM900.println("AT+CMGS=\"+919861369640\""); 
                delay(100);
                
                // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
                SIM900.println("Need Help at:"); 
                 SIM900.print("https://www.google.com/maps/@");
                  SIM900.print(latitude, 6);
                  SIM900.print(',');
                  SIM900.print(longitude, 6);
                  SIM900.println(",14z");
                delay(100);
              
                // End AT command with a ^Z, ASCII code 26
                SIM900.println((char)26); 
                delay(100);
                SIM900.println();
                // Give module time to send SMS
                
       
               
              state = 1;
              delay(5000); 
    }
  if (digitalRead(pin) == LOW) 
  {
      state = 0;
    }*/
        
        
        
 }
    

 

  
