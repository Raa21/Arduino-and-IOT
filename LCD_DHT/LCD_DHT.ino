#include <LiquidCrystal_I2C.h>
#include "DHT.h"
LiquidCrystal_I2C lcd(0x27,20,4); 
#define DHTPIN 5  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(9600);

  dht.begin();
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
 /* lcd.setCursor(0,2);
  lcd.print("Gas Level:               ");
    lcd.setCursor(0,0);
  lcd.print("Temperature:             ");
   lcd.setCursor(0,1);
  lcd.print("Humidity:               ");
   lcd.setCursor(0,3);
  lcd.print("Milk Level:               ");*/
}


void loop()
{
 float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
 
  // Check if any reads failed and exit early (to try again).
  /*if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }*/

  // Compute heat index in Fahrenheit (the default)
 // float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(6,0);
  lcd.print(t);
  lcd.setCursor(10,0);
  lcd.write(0xDF);
  lcd.setCursor(11,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.setCursor(9,1);
  lcd.print(h);
  lcd.setCursor(14,1);
  lcd.print("%");
}
