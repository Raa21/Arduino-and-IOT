
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define sensor A3
int x = A0;
int y = A1;
int z = A2;
LiquidCrystal_I2C lcd(0x27,16,2); //LCD CONNECTED WITH ANALOG PIN ( SCL=A5; SDA=A4)
//const int MQ3=0; //MQ3 SENSOR CONNECTED ANALOG SENSOR(A0) TO A0 PIN (VCC (5V) ,GND)
const int LED=3; //LED LIGHT CONNECTED WITH DIGITAL PIN3
const int buzzer=4; //BUZZER CONNECTED WITH DIGITAL PIN4
#define relay 5 //RELAY  CONNECTED WITH DIGITAL PIN5
int value;
//ultrasonic
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
int safetyDistance;

void setup() {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(sensor, INPUT);
  pinMode(relay,OUTPUT);

  pinMode(LED, OUTPUT);//if you want you can put buzzer in place led or both in the programme
  pinMode(buzzer, OUTPUT);
   pinMode(A2, INPUT);
    pinMode(A1, INPUT);
     pinMode(A0, INPUT);
  
  digitalWrite(relay,HIGH);
        
        digitalWrite(buzzer, LOW);
        digitalWrite(LED, LOW);
  
  lcd.begin(16, 2);//initializing LCD
  /*lcd.setCursor(0,0);
  lcd.print("OM Namah Shivaya");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("AUTOMATIC ");
  delay(400);
  lcd.setCursor(0,1);
  lcd.print("ALCOHOL SENSING");
  delay(400);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ALERT WITH ");
  delay(400);
  lcd.setCursor(0,1);
  lcd.print("ENGINE");
  delay(400);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LOCKING SYSTEM");
  delay(400);
  lcd.setCursor(0,1);
  lcd.print("PROJECT");
  delay(400);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SANTOSH");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("MOHAPATRA");
  delay(400);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1741014022");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MD SAHIL RAZA");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("1741014059");
  delay(500);
  lcd.clear();*/
}







void loop()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

    int sensorValue = analogRead(A0);
   int sensorValue1 = analogRead(A1);
    int sensorValue2 = analogRead(A2);
    Serial.print(sensorValue);
  Serial.print("      ");
  Serial.print(sensorValue1);
  Serial.print("      ");
  Serial.println(sensorValue2);
  
  float adcValue=0;
  for(int i=0;i<10;i++)
  {
    adcValue+= analogRead(sensor);
    delay(10);
  }
    float v= (adcValue/10) * (5.0/1024.0);
    float mgL= 0.67 * v;
    Serial.print("BAC:");
    Serial.print(mgL);
    Serial.print(" mg/L");
    lcd.setCursor(0,0);
    lcd.print(" BAC:   ");
    lcd.print(mgL,4);
    lcd.print("mg/L        ");
   if ( ((sensorValue > 340) && (sensorValue < 350)) && ((sensorValue1 > 343) && (sensorValue1 < 355)) && ((sensorValue2 > 408) && (sensorValue2 < 419)))
  {
    Serial.println("Everything OK!!!");
    lcd.setCursor(0,0);
    lcd.print("Everything OK!!!");
    delay(2000);
      lcd.clear();
    
   if (distance < 10) 
   {
    lcd.setCursor(0,0);
      lcd.print("Distance: ");
        lcd.setCursor(9,0);// Prints string "Distance" on the LCD
      lcd.print(distance);
        lcd.setCursor(14,0);// Prints the distance value from the sensor
      lcd.print("cm   ");
      lcd.setCursor(0,1);
      lcd.print("Danger Ahead");
      delay(2000);
      lcd.clear();
   
     if (mgL > 2.2)
     {
      lcd.setCursor(0,0);
    lcd.print(" BAC:   ");
    lcd.setCursor(0,0);
    lcd.print(mgL,4);
    lcd.print("mg/L        ");
    lcd.setCursor(0,1);
      lcd.print("Drunk ENGINE JAM  ");
     
      digitalWrite(relay,HIGH);
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED, HIGH);
      Serial.println("Keep safety distance please");
       delay(2000);
        lcd.clear();
        
    }
    else
    {
      lcd.setCursor(0,0);
    lcd.print(" BAC:   ");
    lcd.setCursor(0,0);
    lcd.print(mgL,4);
    lcd.print("mg/L        ");
    lcd.setCursor(0,1);
      lcd.print("NORMAL --DRIVE-- ");
     
      digitalWrite(relay,HIGH);
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED, HIGH);
      Serial.println("Keep safety distance please");
       delay(2000);
        lcd.clear();
    
    }
   }
     
    else{
          lcd.setCursor(0,0);
      lcd.print("Distance: ");
        lcd.setCursor(9,0);// Prints string "Distance" on the LCD
      lcd.print(distance);
        lcd.setCursor(14,0);// Prints the distance value from the sensor
      lcd.print("cm   ");
      lcd.setCursor(0,1);
      lcd.print("ALL OK!!");
      delay(2000);
      lcd.clear();
   
     if (mgL > 2.2)
     {
      lcd.setCursor(0,0);
    lcd.print(" BAC:   ");
    lcd.setCursor(0,0);
    lcd.print(mgL,4);
    lcd.print("mg/L        ");
    lcd.setCursor(0,1);
      lcd.print("Drunk ENGINE JAM  ");
     
      digitalWrite(relay,HIGH);
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED, HIGH);
      //Serial.println("Keep safety distance please");
       delay(2000);
        lcd.clear();
      
    }
    else
    {
      lcd.setCursor(0,0);
    lcd.print(" BAC:   ");
    lcd.setCursor(0,0);
    lcd.print(mgL,4);
    lcd.print("mg/L        ");
    lcd.setCursor(0,1);
      lcd.print("NORMAL --DRIVE-- ");
     
      digitalWrite(relay,LOW);
        Serial.println("    Normal");
        digitalWrite(buzzer, LOW);
        digitalWrite(LED, LOW);
       
       delay(2000);
        lcd.clear();
    
    }
        
    }
  }   

  else if ( ((sensorValue > 340) && (sensorValue < 348)) && ((sensorValue1 > 370) && (sensorValue1 < 412)) && ((sensorValue2 > 360) && (sensorValue2 < 404)))
  {
    digitalWrite(buzzer, HIGH);
        digitalWrite(LED, HIGH);
        digitalWrite(relay,HIGH);
    Serial.println("Front Accident!!!");
    lcd.setCursor(0,0);
    lcd.print("Front Accident!!!");
    delay(1000);
    
  }
  else if ( ((sensorValue > 336) && (sensorValue < 345)) && ((sensorValue1 > 270) && (sensorValue1 < 320)) && ((sensorValue2 > 339) && (sensorValue2 < 405)))
  {
    digitalWrite(buzzer, HIGH);
        digitalWrite(LED, HIGH);
        digitalWrite(relay,HIGH);
    Serial.println("Back Accident!!");
    lcd.setCursor(0,0);
    lcd.print("Back Accident!!!");
    delay(1000);
    
  }
  else if ( ((sensorValue > 355) && (sensorValue < 412)) && ((sensorValue1 >343 ) && (sensorValue1 < 353)) && ((sensorValue2 > 339) && (sensorValue2 < 410)))
  {
    digitalWrite(buzzer, HIGH);
        digitalWrite(LED, HIGH);
        digitalWrite(relay,HIGH);
    Serial.println("Right Accident!!");
    lcd.setCursor(0,0);
    lcd.print("Right Accident!!!");
    delay(1000);
    
  }
  else if ( ((sensorValue > 270 ) && (sensorValue < 328)) && ((sensorValue1 > 340) && (sensorValue1 < 351)) && ((sensorValue2 > 350) && (sensorValue2 < 409)))
  {
    digitalWrite(buzzer, HIGH);
        digitalWrite(LED, HIGH);
        digitalWrite(relay,HIGH);
    Serial.println("Left Accident!!");
    lcd.setCursor(0,0);
    lcd.print("Left Accident!!!");
    delay(1000);
    
  }
  lcd.clear();
}
