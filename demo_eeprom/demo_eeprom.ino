#include <EEPROM.h>
String retrievedString;
int l = 0;
int flag = 0;
int f = 0;

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);

  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}


int str_leg( int addrOffset)
{
  int len = EEPROM.read(addrOffset);
  return int(len);
}

String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];

  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)

  return String(data);
}


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  l = str_leg(0);
  Serial.println(l);
  retrievedString = readStringFromEEPROM(0);
  Serial.println(retrievedString);
  if ( l < 10)
  {
    f = 0;
   // Serial.println("Enter Code for registration:");
  }
  else
  {
    f = 1;
  }
}



void loop() 
{
  retrievedString = readStringFromEEPROM(0);
  delay(30);
  String code;
 while (Serial.available())
 {
  char c = Serial.read();
  code += c;
  Serial.println(code); 
 
 if( code.length() > 10)
{

 if(( l < 10 ) && (f == 0)) 
 {
  Serial.println("Enter Code for registration:");
   writeStringToEEPROM(0, code); 
   f = 1;
 }

  if ( code == retrievedString )
 {
  flag = 1;
  Serial.println(flag);
 }
 /*else
 {
  flag = 0;
   Serial.println(flag);
 }*/
}
  if ((code.length() > 0) && (code.length() < 10))
  {
  if  ( code == "reg" )
    {
        if  (flag == 1)
       {
        flag = 0;
         Serial.println("Registration");
         delay(1000);
       }
       else if  (flag == 0)
       {
        Serial.println("Enter code for settings:");
         delay(1000);
       }
 }

 if  ( code == "del" )
 {
        if  (flag == 1)
       {
        flag = 0;
         Serial.println("Deletion");
         delay(1000);
       }
       else if  (flag == 0)
       {
        Serial.println("Enter code for settings:");
         delay(1000);
       }
 }
 else
 {
  Serial.println("Enter correct registration code:");
  //flag = 0;
 }
}
 }
 if ( f == 1)
 { 
  Serial.println("check print");
   Serial.print("flag:");
    Serial.println(flag);
  delay(1000);
 }
 else
 {
  Serial.println("Enter registration");
  delay(1000);
 }
code = " ";

}
