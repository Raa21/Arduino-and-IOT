/*
* NodeMCU I2C 16x2 LCD
* Created by TheCircuit
*/
#include <ESP8266WiFi.h> 
#include <Wire.h>  // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 
LiquidCrystal_I2C lcd(0x27, 16, 2);

float value=0;
float rev=0;
int rpm;
int oldtime=0;
int time1;

const char* ssid     = "Redmi Note 5 Pro";// replace subscribe with your WiFi SSID(Name)
const char* password = "kshitiz123";//replace with Your Wifi Password name
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "CAN07IQSJ3NJTHSB"; 

void isr() //interrupt service routine
{
rev++;
}

void setup()
{
  Serial.begin(115200);
   Wire.begin(2,0);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.print(" Hello Makers ");
  lcd.setCursor(9,1);
  lcd.print(" OK!! ");// Start Printing
               //initialize LCD
attachInterrupt(14,isr,RISING); //attaching the interrupt

Serial.println("Connecting to ");
       Serial.println(ssid);
//  Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
   Serial.println("");
   Serial.println("WiFi connected");
}

void loop()
{
   
delay(1000);

WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  
detachInterrupt(0);           //detaches the interrupt
time1=millis()-oldtime;        //finds the time 
rpm=(rev/time1)*60000;         //calculates rpm
oldtime=millis();             //saves the current time
rev=0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("___TACHOMETER___");
lcd.setCursor(0,1);
lcd.print(     rpm);
lcd.print(" RPM");
lcd.print("   ");

String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(rpm);
  url+="\r\n";
  
  // Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
               Serial.println("Send to ThingSpeak.\n");
client.stop();
  Serial.println("Wait for 1 sec to update next datapack in thingSpeak");

attachInterrupt(0,isr,RISING);

}
