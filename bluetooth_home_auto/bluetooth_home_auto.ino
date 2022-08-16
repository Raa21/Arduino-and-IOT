#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
#include <Wire.h>
#include <TimerOne.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//String v;

volatile int i=0;               // Variable to use as a counter
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin =11;



void zero_cross_detect() 
{    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);
}     
void dim_check() 
{                   
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(AC_pin, HIGH);  // turn on light       
      i=0;  // reset time step counter                         
      zero_cross=false;    // reset zero cross detection
    } 
    else {
      i++;  // increment time step counter                     
}}}                                      

void d()
{
     Wire.begin();
lcd.begin(16,2);
lcd.backlight();
 lcd.setCursor(0,0);
  lcd.print("BL1");
  lcd.setCursor(4,0);
  lcd.print("BL2");
  lcd.setCursor(8,0);
  lcd.print("BL3");
  lcd.setCursor(12,0);
  lcd.print("FAN");
   //lcd.print("CONNECTED.....");
   return;
}

void setup()

{
 Wire.begin();
 lcd.begin(16,2);
lcd.backlight();
mySerial.begin(9600);   
Serial.begin(9600); 
d();
  lcd.setCursor(0,1);
  lcd.print("OFF");
  lcd.setCursor(4,1);
  lcd.print("OFF");
  lcd.setCursor(8,1);
  lcd.print("OFF");
  lcd.setCursor(12,1);
  lcd.print("OFF");
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);


//d();
}

void loop()

{

if (mySerial.available())
{
 //d();

long m=0;
char v=0;
 v=(mySerial.read());
  m= Serial.parseInt(); 
 Serial.print(m);


 if (v=='a')
 {
  lcd.setCursor(0,1);
  lcd.print(" ON");
  digitalWrite(3,HIGH);
  //Serivl.print(p1);  
 }
 if (v=='A')
 {

  lcd.setCursor(0,1);
  lcd.print("OFF");
  digitalWrite(3,LOW);
 }
  if (v=='b')
 {
  lcd.setCursor(4,1);
 // lcd.clear();
  lcd.print(" ON");
  digitalWrite(4,HIGH);
 }
  if (v=='B')
 {
  lcd.setCursor(4,1);
  lcd.print("OFF");
  digitalWrite(4,LOW);
 
 }
 
  if (v=='c')
 {
  lcd.setCursor(8,1);
  lcd.print(" ON");
  digitalWrite(5,HIGH);
 }
  if (v=='C')
 {
  lcd.setCursor(8,1);
  lcd.print("OFF");
  digitalWrite(5,LOW);
 
 }
   if (v=='d')
 {
  lcd.setCursor(12,1);
  lcd.print(" ON");
  digitalWrite(6,HIGH);
 }
  if (v=='D')
 {
  lcd.setCursor(12,1);
  lcd.print("OFF");
   lcd.setCursor(15,1);
  lcd.print(" ");
  digitalWrite(6,LOW);
 }
  if (v=='j')
    {
        lcd.setCursor(0,1);
        lcd.print(" ON");
        digitalWrite(3,HIGH);
        lcd.setCursor(4,1);
        lcd.print(" ON");
        digitalWrite(4,HIGH);
        lcd.setCursor(8,1);
        lcd.print(" ON");
        digitalWrite(5,HIGH);
        lcd.setCursor(12,1);
        lcd.print(" ON");
        digitalWrite(6,HIGH);
    }
 if (v=='J')
    {
        lcd.setCursor(0,1);
        lcd.print("OFF");
        digitalWrite(3,LOW);
        lcd.setCursor(4,1);
        lcd.print("OFF");
        digitalWrite(4,LOW);
        lcd.setCursor(8,1);
        lcd.print("OFF");
        digitalWrite(5,LOW);
        lcd.setCursor(12,1);
        lcd.print("OFF");
        digitalWrite(6,LOW);
        lcd.print(" ");

    }

if(v=='o')
{
lcd.setCursor(12,1);
      lcd.print("000");
        lcd.print("%");
  
}

if( digitalRead(6)== HIGH)
{    
if (m>0 && m<=100)
{

  if(m>0 && m<=9)
  {
   lcd.setCursor(12,1);
   lcd.print("00");
        lcd.print(m);
         lcd.print("%");
  }
   if(m>10 && m<=99)
  {
   lcd.setCursor(12,1);
   lcd.print("0");
        lcd.print(m);
        lcd.print("%");
  }
  if(m==100)
  {
     lcd.setCursor(12,1);
      lcd.print(m);
        lcd.print("%");
  }

  
}
}
}
}
