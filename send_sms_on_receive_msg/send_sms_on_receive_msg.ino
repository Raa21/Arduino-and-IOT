
#include <SoftwareSerial.h>

char incoming_char=0;
int state = 0;
const int pin = 9;


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
               
                delay(100);
              
                // End AT command with a ^Z, ASCII code 26
                SIM900.println((char)26); 
                delay(100);
                SIM900.println();
     }
      else
      {
        Serial.println("Wrong Command");
        
              SIM900.print("AT+CMGF=1\r"); 
                delay(100);
              
                // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
                // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
                SIM900.println("AT+CMGS=\"+917008723446\""); 
                delay(100);
                
                // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
                SIM900.println("Need Help at:"); 
              
                // End AT command with a ^Z, ASCII code 26
                SIM900.println((char)26); 
                delay(100);
                SIM900.println();
      }
    }

    delay(100); 
    //Print the incoming character to the terminal
     
    }
          
     
        
        
 }
    

 

  
