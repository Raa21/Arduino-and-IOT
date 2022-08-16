#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int xInput = A0;
const int yInput = A1;
const int zInput = A2;
byte Heart[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 0;
int RawMax = 1023;
int count ;

// Take multiple samples to reduce noise
const int sampleSize = 10;

void setup() 
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  lcd.init();
   lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
   lcd.print("***EARTHQUAKE***   ");
  lcd.setCursor(0, 1);
  lcd.print("****DETECTOR****  ");
  lcd.createChar(0, Heart);
  delay(5000);
  lcd.clear();
}

void loop() 
{
 
  //Read raw values
          int xRaw = ReadAxis(xInput);
          int yRaw = ReadAxis(yInput);
          int zRaw = ReadAxis(zInput);
        
          // Convert raw values to 'milli-Gs"
          long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000);
          long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000);
          long zScaled = map(zRaw, RawMin, RawMax, -3000, 3000);
        
          // re-scale to fractional Gs
          float xAccel = xScaled / 1000.0;
          float yAccel = yScaled / 1000.0;
          float zAccel = zScaled / 1000.0;
        
          Serial.print("X, Y, Z  :: ");
          Serial.print(xRaw);
          Serial.print(", ");
          Serial.print(yRaw);
          Serial.print(", ");
          Serial.print(zRaw);
          Serial.print(" :: ");
          Serial.print(xAccel,0);
          Serial.print("G, ");
          Serial.print(yAccel,0);
          Serial.print("G, ");
          Serial.print(zAccel,0);
          Serial.println("G");
              
              if( ((xRaw > 505) && (xRaw < 508)) && ((zRaw > 608) && (zRaw < 611)))
              {
                lcd.setCursor(0, 0);
               lcd.print("STATUS:");
              lcd.setCursor(7, 0);
              lcd.print("NORMAL    ");
               lcd.setCursor(13, 0);
                lcd.write(0);
               lcd.setCursor(0, 1);
               lcd.print("!!! CHILL !!!    ");
                digitalWrite( 3, 0);    
                  
              }  
        else 
        {
                lcd.setCursor(0, 0);
               lcd.print("STATUS:");
              lcd.setCursor(7, 0);
              lcd.print("WARNING!!!    ");
              lcd.setCursor(0, 1);
               lcd.print("!! EARTHQUAKE !!");
              
          digitalWrite(3 , 1);
          delay(1000); 
        }
        delay(200); 
    
}        

// Take samples and return the average
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
  reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}
