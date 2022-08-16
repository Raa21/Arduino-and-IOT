#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <millisDelay.h>
 
millisDelay timerDelay;
int pulsesensor = 0;
int counter = 0;
int bpm = 0;
int test = 0;
int rate = 0;
int r1,r2,r3,r4,r5 = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
 
  Serial.begin(9600);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("Heart Beat");
  lcd.setCursor(2, 1);
  lcd.print("Sensor");
  lcd.backlight();
}
 
void loop() {
 
  pulsesensor = analogRead(A0);
  delay(20);
  Serial.println(pulsesensor);
  
  if (pulsesensor < 70)
  {
    r1 = 1;
    r2 = 1;
    r3 = 1;
    r4 = 1;
    r5 = 1;
    lcd.setCursor(0, 0);
    lcd.print("Heart Rate:");
    lcd.setCursor(2, 1);
    lcd.print("Please Wait");
    delay(6000);
    test = 1;
    timerDelay.start(15000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Rate:");
    lcd.setCursor(2, 1);
    lcd.print("Scanning");
  }  
 
  if (test == 1) {
    if (pulsesensor == 540 && r1 == 1)
    {
      r2 = 0;
      r3 = 0;
      r4 = 0;
      r5 = 0;
      counter++;
      delay(500);
      Serial.print("counter:");
      Serial.println(counter);
      
    }
    else if (pulsesensor == 530 && r2 == 1)
    {
      counter++;
      delay(500);
      Serial.print("counter:");
      Serial.println(counter);
      r1 = 0;
      r3 = 0;
      r4 = 0;
      r5 = 0;
    }
    else if (pulsesensor == 520 && r3 == 1)
    {
      counter++;
      delay(500);
      Serial.print("counter:");
      Serial.println(counter);
      r2 = 0;
      r1 = 0;
      r4 = 0;
      r5 = 0;
    }
    else if (pulsesensor == 512 && r4 == 1)
    {
      counter++;
      delay(500);
      Serial.print("counter:");
      Serial.println(counter);
      r2 = 0;
      r3 = 0;
      r1 = 0;
      r5 = 0;
    }
    else if (pulsesensor == 500 && r5 == 1)
    {
      counter++;
      delay(500);
      Serial.print("counter:");
      Serial.println(counter);
      r2 = 0;
      r3 = 0;
      r4 = 0;
      r1 = 0;
    }
  
  if (timerDelay.isFinished())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Rate:");
    lcd.setCursor(2, 1);
    lcd.print("Remove");
    bpm = counter * 4;
    rate = 1;
    test = 0;
    counter = 0;
    Serial.println("bpm:");
    Serial.println(bpm);
    delay(5000);
    lcd.clear();
 
  }
  }
  if (rate == 1)
  {
    if (bpm > 60 && bpm < 100 || bpm == 60 || bpm == 100)
    {
      normal();
      rate = 0;
      delay(5000);
      bpm = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Heart Rate:");
    }
    else if (bpm < 60)
    {
      slow();
      rate = 0;
      delay(5000);
      bpm = 0;
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Heart Rate:");
    }
    else if (bpm > 100)
    {
      fast();
      rate = 0;
      delay(5000);
      bpm = 0;
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Heart Rate:");
    }
  }
}
void slow()
{
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate:");
  lcd.setCursor(2, 1);
  lcd.print("Slow");
  lcd.setCursor(9, 1);
  lcd.print("BPM:");
  lcd.setCursor(13, 1);
  lcd.print(bpm);
}
void normal()
{
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate:");
  lcd.setCursor(2, 1);
  lcd.print("normal");
  lcd.setCursor(9, 1);
  lcd.print("BPM:");
  lcd.setCursor(13, 1);
  lcd.print(bpm);
}
void fast()
{
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate:");
  lcd.setCursor(2, 1);
  lcd.print("Fast");
  lcd.setCursor(9, 1);
  lcd.print("BPM:");
  lcd.setCursor(13, 1);
  lcd.print(bpm);
}
