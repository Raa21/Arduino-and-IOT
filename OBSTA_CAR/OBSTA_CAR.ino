#include <Servo.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo_motor;
int trig = 3;      // trig pin of HC-SR04
int echo = 4;     // Echo pin of HC-SR04
long duration, distance, cm;
int m1 = 8;       //REVerse motion of Left motor
int m2 = 9;       //ForWarD motion of Left motor
int m3 = 10;      //REVerse motion of Right motor
int m4 = 13;  
int buzzer = 2;
int led = 7;
int green = 12;
int en1 = 5;
int en2 = 11;
int r, l;//ForWarD motion of Right motor
boolean goesForward = false;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Obstacle  ");
  lcd.setCursor(0, 1);
  lcd.print("Avoiding Car");
  delay(2000);
  pinMode(m1, OUTPUT);      // set Motor pins as output
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
   pinMode(green, OUTPUT);
   pinMode(en1, OUTPUT); 
    pinMode(en2, OUTPUT); 
  pinMode(trig, OUTPUT);         // set trig pin as output
  pinMode(echo, INPUT);   
 servo_motor.attach(6); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = dis();
  delay(100);
  distance = dis();
  delay(100);
  distance = dis();
  delay(100);
  distance = dis();
  delay(100);
 // put your setup code here, to run once:
  
}

void loop() {
  
  int distanceRight = 0;
  int distanceLeft = 0;// put your main code here, to run repeatedly:
  distance = dis();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:     ");
  lcd.setCursor(9, 0);
  lcd.print(distance);
  lcd.setCursor(12, 0);
  lcd.print("cm ");
  lcd.setCursor(0, 1);
  lcd.print("ALL CLEAR!!      ");
  
    // If you dont get proper movements of your robot then alter the pin numbers
    
/* if ((distance <= 30) && (distance > 20))
  {
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:     ");
  lcd.setCursor(9, 0);
  lcd.print(distance);
  lcd.setCursor(12, 0);
  lcd.print("cm ");
     lcd.setCursor(0, 1);
  lcd.print("DANGER INCOMING!      ");
  digitalWrite(led, LOW);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
   slow(); 
  }*/
  if (distance <= 50) 
  {
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:     ");
  lcd.setCursor(9, 0);
  lcd.print(distance);
  lcd.setCursor(12, 0);
  lcd.print("cm ");
     lcd.setCursor(0, 1);
  lcd.print("DANGER AHEAD!!      ");
     digitalWrite(led, HIGH);
     digitalWrite(green, LOW);
     digitalWrite(buzzer, HIGH);
     moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    digitalWrite(buzzer, LOW);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
     else{
       digitalWrite(led, LOW);
       digitalWrite(green, HIGH);
       digitalWrite(buzzer, LOW);
    moveForward(); 
  }
  
  
 delay(500);
}
long dis()
{
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);                        // The same pin is used to read the signal from the PING))): a HIGH, pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH); 
  cm =  duration/ 29 / 2;
  return cm;
}
void moveStop(){
  
  digitalWrite(m2, LOW);
  digitalWrite(m4, LOW);
  digitalWrite(m1, LOW);
  digitalWrite(m3, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(m4, HIGH);
    digitalWrite(m2, HIGH);
  
    digitalWrite(m3, LOW);
    digitalWrite(m1, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

  digitalWrite(m3, HIGH);
  digitalWrite(m1, HIGH);
  
  digitalWrite(m4, LOW);
  digitalWrite(m2, LOW);
  
}

void turnRight(){

  digitalWrite(m4, HIGH);
  digitalWrite(m1, HIGH);
  
  digitalWrite(m3, LOW);
  digitalWrite(m2, LOW);
  
  delay(500);
  
  digitalWrite(m4, HIGH);
  digitalWrite(m2, HIGH);
  
  digitalWrite(m3, LOW);
  digitalWrite(m1, LOW);
 
  
  
}

void turnLeft(){

  digitalWrite(m3, HIGH);
  digitalWrite(m2, HIGH);
  
  digitalWrite(m4, LOW);
  digitalWrite(m1, LOW);

  delay(500);
  
  digitalWrite(m4, HIGH);
  digitalWrite(m2, HIGH);
  
  digitalWrite(m3, LOW);
  digitalWrite(m1, LOW);
}
int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = dis();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = dis();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}
/*void slow()
{
  analogWrite(en1, 90);
  analogWrite(en2, 90);
  digitalWrite(m4, HIGH);
    digitalWrite(m2, HIGH);
  
    digitalWrite(m3, LOW);
    digitalWrite(m1, LOW); 
}*/
