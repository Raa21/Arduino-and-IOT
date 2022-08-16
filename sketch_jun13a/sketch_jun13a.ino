#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial serial_gps(4, 5); // RX = pin 10, TX = pin 11
SoftwareSerial mySerial(2, 3);
TinyGPSPlus gps;
double latitude, longitude;<br>int z,counterCommand;
boolean found = false;
boolean autoReset = false;<br>void setup() {
  Serial.begin(9600);
  serial_gps.begin(9600);
  mySerial.begin(9600);
  Serial.println("GPS Mulai");
  //## order of AT-Command to remove when tool is first turned on ##//
  mySerial.listen();
  while(counterCommand<=3)// meaning that if the order at command is less than 3 then do below
  {
    switch(counterCommand)
    {
      case 0: atCommand("AT",1,"OK");break; // order at command 1: test micro communication with SIM
      case 1: atCommand("AT+CMGF=1",1,"OK");break;// order 2: setting SIM800 with mode text
      case 2: atCommand("AT+CMGL="ALL",0",2,"OK");break;//3: read all saved messages without changing the status. 
                                                          // the intent of the status is if the sms has not been read then it will not be changed to<br>                                                          // readable if using this at command 
      case 3: atCommand("AT+CMGD=1,4",1,"OK");break;  // delete the entire contents of the sms on the card (just in case when the sms operatore)<br>    }
  }
//##############################
  counterCommand = 0;// the order is made 0 to do the program that is in the loop<br>}<br>void loop() {
  serial_gps.listen();
  while(serial_gps.available()) {
    gps.encode(serial_gps.read());
  }
  if(gps.location.isUpdated()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    String valLat = String(latitude);
    String valLong = String(longitude);
    String link = "http://www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
    Serial.print("Link Google Maps : ");
    Serial.println(link);
    Serial.print("Satellite Count : ");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude : ");
    Serial.println(latitude, 6);
    Serial.print("Longitude : ");
    Serial.println(longitude, 6);
    Serial.print("Speed MPH : ");
    Serial.println(gps.speed.mph());
    Serial.print("Altitude Feet : ");
    Serial.println(gps.altitude.feet());
    Serial.println("");
    mySerial.listen();
    atCommand("AT+CMGF=1",1,"OK");
    atCommand("AT+CMGS="+6281553718364"",1,">");
    atCommand("Latitude:""+valLat+"",Longitude""+valLong+""",1,">");
    Serial.println("Mengirim Char Ctrl+Z / ESC untuk keluar dari menu SMS");
    mySerial.write((char)26);
    delay(10000);
  }
  //delay(10000);
}
void atCommand(String iCommand, int timing, char myText[])
{
  String onOff = String(myText);
  Serial.println("###Start###");
  Serial.print("Command Ke ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ");
  Serial.print(counterCommand);
  Serial.print("   Kirim=>");Serial.println(iCommand);
  while(timing>z)
  {
    mySerial.println(iCommand);
    if(mySerial.find(myText))
    {
      found = true;
      break;
    }
    Serial.print(z);Serial.print(",");
    z++;
  }
  if(found == true)
  {
    autoReset = false;
    
    counterCommand++;
    Serial.println("==============================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> oke");
  }
  else
  {
    
      mySerial.write("AT+CMGF=1");
      delay(1000);
      mySerial.write("AT+CMGD=1,4");
      delay(1000);
      Serial.print("nautoReset=truen");
      autoReset = true;
      Serial.println("--------============>>>>>>>> AT Command Error");
      Serial.println("--------============>>>>>>>> Proses reset");
      //digitalWrite(resetPin, HIGH);
      //delay(200);
      //digitalWrite(resetPin, LOW);
      //delay(15000);
      counterCommand = 0;
    
  }
  if(counterCommand >=100)
  {
    counterCommand = 0;
  }
  found = false;
  z=0;
 Serial.println("***end***");
  
}
