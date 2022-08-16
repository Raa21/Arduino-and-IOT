
#include <EEPROM.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int led = 9;
int st = 8;
long i = 0;
long h,m,s;
int sln = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(st , INPUT);
  digitalWrite(led, LOW);
 //Sets digital pin 13 as output pin
  lcd.init();
 //lcd.begin(16,2);
      lcd.backlight();
      lcd.clear();
      lcd.setCursor(0, 0);
  lcd.print("  Developed By:    ");
  lcd.setCursor(0, 1);
  lcd.print(" DEMON BROTHERS   ");
  delay(5000);
  lcd.clear();
  checkLedState();
}
void loop()
{
delay(30);
  String t; 
  while(Serial.available())
  { 
    t += (char)Serial.read(); 
    Serial.println(t);
  }
  
  if(t.length())
  { 
    if(t == "1")
    { 
       
  // save the current LED state in the EEPROM
    
      digitalWrite(led, HIGH); 
     Serial.write(sln);
     lcd.setCursor(10, 0);
  lcd.print("  LIVE      ");
    }
   
   else if (t == "0") 
    {
      sln = sln + 1; 
     EEPROM.write(0, sln);
     Serial.println("sln");
     Serial.println(sln);
     digitalWrite(led, LOW);  
     Serial.write("Hold");
     lcd.setCursor(10, 0);
    lcd.print("  OFF      ");
    }

  }
 /*if ( digitalRead(st) == 1)
    {
     i = i+1;
     h = i/3600;
     m = (i%3600)/60;
     s = (i%3600)%60;
     Serial.println(h);
     Serial.print(":");
     Serial.print(m);
     Serial.print(":");
     Serial.print(s);
     lcd.setCursor(0, 1);
     lcd.print("TIME:      ");
  lcd.setCursor(5, 1);
  lcd.print(h);
  lcd.setCursor(7, 1);
  lcd.print(":      ");
  lcd.setCursor(8, 1);
  lcd.print(m);
  lcd.setCursor(10, 1);
  lcd.print(":      ");
  lcd.setCursor(11, 1);
  lcd.print(s);
     delay(1000);
     
    }
   else if ( digitalRead(st) == 0) 
    {
      
     Serial.println("Total Duration:");
     Serial.print(h);
     Serial.print(":");
     Serial.print(m);
     Serial.print(":");
     Serial.print(s);
     lcd.setCursor(0, 1);
     lcd.print("TT:      ");
  lcd.setCursor(4, 1);
  lcd.print(h);
  lcd.setCursor(6, 1);
  lcd.print("hr:      ");
  lcd.setCursor(9, 1);
  lcd.print(m);
  lcd.setCursor(11, 1);
  lcd.print("m:      ");
  lcd.setCursor(13, 1);
  lcd.print(s);
  lcd.setCursor(15, 1);
  lcd.print("s      ");
     delay(1000);
     
    }  */
else
{
  Serial.println("Slno:");
   Serial.println(sln);
   lcd.setCursor(0, 0);
  lcd.print("Slno:      ");
  lcd.setCursor(5, 0);
  lcd.print(sln);
  lcd.setCursor(0, 1);
  lcd.print("TT:      ");
  lcd.setCursor(4, 1);
  lcd.print(h);
  lcd.setCursor(6, 1);
  lcd.print("hr:      ");
  lcd.setCursor(9, 1);
  lcd.print(m);
  lcd.setCursor(11, 1);
  lcd.print("m:      ");
  lcd.setCursor(13, 1);
  lcd.print(s);
  lcd.setCursor(15, 1);
  lcd.print("s      ");
     delay(1000);                      
}

}
void checkLedState() 
{
   Serial.println("Slno after restart: ");
   sln = EEPROM.read(0);
   Serial.print(sln);
   lcd.setCursor(0, 0);
  lcd.print("Slno:            ");
  lcd.setCursor(5, 0);
  lcd.print(sln);
}
