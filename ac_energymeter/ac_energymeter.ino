/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = A0;
float x = 0;
float y, cost;
float power = 0;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("    IOT BASED    ");
  lcd.setCursor(0,1);
  lcd.print("AC ENERGY METER!");
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = analogRead(pushButton);
  // print out the state of the button:
  Serial.print(buttonState);
  if (buttonState < 30)
  {
    x = x+1;
    y = x/10; 
  }
   Serial.print(",");
    Serial.println(y,2);
     power = y*0.1;
    cost = y*5;
    Serial.print("Total Power:");
    Serial.println(power,2);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Units:");
    lcd.setCursor(6,0);
    lcd.print(y,1);
    lcd.setCursor(0,1);
    lcd.print("kWh:   ");
    lcd.setCursor(4,1);
    lcd.print(power,2);
    lcd.setCursor(9,1);
    lcd.print("Rs:  ");
    lcd.setCursor(12,1);
    lcd.print(cost,2);
    
    
    
    
   
  delay(10);        // delay in between reads for stability
}
