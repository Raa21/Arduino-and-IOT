#include <SoftwareSerial.h>
String *incoming=0;
SoftwareSerial SIM900(2, 3); 
void setup() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // For serial monitor
  Serial.begin(9600); 
  // Give time to your GSM shield log on to network
  delay(20000);

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

/*void loop() {
  // Display any text that the GSM shield sends out on the serial monitor
  if(SIM900.available() >0) 
  {
    //Get the character from the cellular serial port
    incoming_char=SIM900.read(); 
    //Print the incoming character to the terminal
    Serial.print(incoming_char); 
  }
}*/
void loop()
{
    String buffer = SIM900.readString();

    if (buffer.startsWith("\r\n+CMT: "))
    {
       /* for( int i = 0; i < 14 ; i++)
        {
          incoming[i] = buffer[i];
          Serial.println(incoming[i]);
        }*/
       
        // Remove first 51 characters
        buffer.remove(0, 51);
        int len = buffer.length();
        // Remove \r\n from tail
        buffer.remove(len - 2, 2);
        
        Serial.println(buffer);
        
      if(buffer == "Location")
      {
        Serial.println("Success");
      }
      else
      {
        Serial.println("Wrong Command");
      }
    }

    delay(100);
}
