#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 
LiquidCrystal_I2C lcd(0x27, 16, 2);
float rev=0;
int rpm;
int oldtime=0;
int time1;



void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);
 lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.print(" Hello Makers ");
  lcd.setCursor(9,1);
  lcd.print(" OK!! ");
 pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
 
  digitalWrite(9, 0);
  analogWrite(11, 0);
  digitalWrite(8, 0);
  delay(2000);
}

void loop() {
  while(Serial.available()) {
delay(10);
char voice =Serial.read();
Serial.println(voice);
  // put your main code here, to run repeatedly:
 
    
    if ((voice == 'H') || (voice == 'h') )
    {
      lcd.setCursor(0,0);
      lcd.print("___TACHOMETER___");
      lcd.setCursor(0,1);
      lcd.print("937");
      lcd.setCursor(5,1);
      lcd.print(" RPM");
      analogWrite(11, 255);
      digitalWrite(8, 1);
    }
    else if ((voice == "M") || (voice == 'm') )
    {
       lcd.setCursor(0,0);
      lcd.print("___TACHOMETER___");
      lcd.setCursor(0,1);
      lcd.print("577");
      lcd.setCursor(5,1);
      lcd.print(" RPM");
      analogWrite(11, 180);
      digitalWrite(8, 1);
    }
    else if ((voice == "L") || (voice == 'l') )
    {
       lcd.setCursor(0,0);
      lcd.print("___TACHOMETER___");
      lcd.setCursor(0,1);
      lcd.print("253");
      lcd.setCursor(5,1);
      lcd.print(" RPM");
      analogWrite(11, 100);
      digitalWrite(8, 1);
    }
    else if ((voice == "S") || (voice == 's') )
    {
       lcd.setCursor(0,0);
      lcd.print("___TACHOMETER___");
      lcd.setCursor(0,1);
      lcd.print("000");
      lcd.setCursor(5,1);
      lcd.print(" RPM");
      analogWrite(11, 0);
      digitalWrite(8, 0);
    }
    
}
 delay(1000);          //detaches the interrupt
}
