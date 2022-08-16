#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);

const int trigPin = 10;
const int echoPin = 11;
const int buzzer=4;
#define relay 5
#define sensor 3

long duration;
int distance;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin(); 
   myservo.attach(9); 
   lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(sensor, INPUT);
  pinMode(relay,OUTPUT);
   pinMode(buzzer, OUTPUT);

   digitalWrite(buzzer, 0);
    digitalWrite(relay, 0);
    myservo.write(0); 
}

void loop() {
  // put your main code here, to run repeatedly:
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
  
Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  int x = digitalRead(sensor);

  if( distance <= 8 )
  {
    digitalWrite(relay, 0);
    myservo.write(0); 
    
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(6,0);
    lcd.print(mlx.readObjectTempF());
    lcd.setCursor(14,0);
     lcd.write(0xDF);
     lcd.setCursor(15,0);
    lcd.print("F");
    if ( mlx.readObjectTempF() > 99)
    {
      digitalWrite(buzzer, 1);
      lcd.setCursor(0,1);
    lcd.print("High Fever!!!");
    }
    else
    {
       digitalWrite(buzzer, 0);
    lcd.setCursor(0,1);
    lcd.print("Please Sanitize ");
    }
     delay(3000);
     lcd.clear();
    
  }
  if( distance > 8 )
  {
     digitalWrite(buzzer, 0);
    digitalWrite(relay, 0);
    myservo.write(0); 
    lcd.setCursor(0,0);
    lcd.print("Come Closer...");
    delay(1000);
     lcd.clear();
  }
  if( x == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("THANK YOU FOR");
     lcd.setCursor(0,1);
    lcd.print("YOUR SUPPORT");
   
    digitalWrite(buzzer, 0);
    digitalWrite(relay, 1);
    delay(500);
    digitalWrite(relay, 0);
    delay(2000);
    myservo.write(180); 
    delay(3000);
    myservo.write(0);
    lcd.clear(); 
  }
 /* if( x == 0)
  { 
    digitalWrite(buzzer, 0);
    digitalWrite(relay, 0);
    myservo.write(0); 
  }*/
  
}
