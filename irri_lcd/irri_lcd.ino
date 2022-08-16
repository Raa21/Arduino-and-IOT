#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int x = A0;
char str;
int motor = 6; 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Automatic Plant ");
  lcd.setCursor(0, 1);
  lcd.print("Watering System");
  delay(2000);
pinMode(x, INPUT);
pinMode(motor, OUTPUT);
digitalWrite(motor, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
int y = analogRead(x);
y = map(y, 0, 1023, 100, 0);

lcd.setCursor(0, 0);
  lcd.print("Soil Moist:    ");
  lcd.setCursor(11, 0);
  lcd.print(y);
  lcd.setCursor(14, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Motor Status:"); 
  lcd.setCursor(13, 1);
  lcd.print("OFF  ");
Serial.print(y);

if( y > 60)
{
  digitalWrite(motor, 0);
}
else{
  lcd.setCursor(13, 1);
  lcd.print("ON   ");
  digitalWrite(motor, 1);
}
delay(100);
}
