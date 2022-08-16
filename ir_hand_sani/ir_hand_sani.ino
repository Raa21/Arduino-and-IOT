#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int let;
int count = 0;
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" HAND SANITISER ");
  lcd.setCursor(0, 1);
  lcd.print("No of person:");
  delay(600);
 //  pinMode (vcc, OUTPUT);
  // pinMode (gnd, OUTPUT);
  pinMode (5, INPUT);
  pinMode (9, OUTPUT);

  // initialize serial communication:
  Serial.begin(9600);
}
void loop()
{
  //digitalWrite(vcc, HIGH);                    // establish variables for duration of the ping,and the distance result in inches and centimeters:
  int x = digitalRead(5);
  Serial.print(x);
 
  
  
  if (x == 0){
    digitalWrite(9, HIGH); //on
    delay(2000);
    digitalWrite(9, LOW); //off
    count++;
    Serial.println(count);
    lcd.setCursor(0, 0);
    lcd.print(" HAND SANITISER ");
    lcd.setCursor(0, 1);
    lcd.print("No of person:");
    lcd.setCursor(14, 1);
    lcd.print(count);
    delay(3000);
    let = 1;

  }
  else if (x == 1)
  {
    let = 0;
  }
  else {
    digitalWrite(9, LOW); //off
  }
}
