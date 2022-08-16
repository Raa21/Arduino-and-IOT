//#include <LiquidCrystal.h>

//LiquidCrystal lcd(6 , 7, 5, 4, 3, 2);
//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27,16,2);
 
long duration;
int distanceCm, distanceInch;

const int trigPin = 11;
const int echoPin = 10;
void setup() {
 Serial.begin(9600); 
//lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
//lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  //lcd.backlight();
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode (8, OUTPUT);
pinMode (9, OUTPUT);
pinMode (12, OUTPUT);
pinMode (7, OUTPUT);

}

void loop() {
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;
Serial.println( distanceCm );
/*lcd.clear();
 lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
  lcd.setCursor(10,0);
  lcd.print(distanceCm);*/

/*lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
lcd.print("Distance: "); // Prints string "Distance" on the LCD
lcd.print(distanceCm); // Prints the distance value from the sensor
lcd.print("  cm");
delay(10);
lcd.setCursor(0,1);
lcd.print("Distance: ");
lcd.print(distanceInch);
lcd.print("inch");
delay(10);*/

/*if ( distanceCm >= 100 )
{
   /*lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
  lcd.setCursor(10,0);
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("STATS:");
  lcd.setCursor(6,1);
  lcd.print("!!GOOD!!     ");
   
  digitalWrite( 8 , HIGH );
  digitalWrite( 9 , LOW );
  digitalWrite( 12 , LOW );
  digitalWrite( 7 , LOW );
}
else if (( distanceCm < 100 ) && ( distanceCm >= 80 ))
{
  /* lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
  lcd.setCursor(10,0);
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("STATS:");
  lcd.setCursor(6,1);
  lcd.print("!!GOOD!!   ");
  digitalWrite( 12 , LOW );
  digitalWrite( 7 , LOW );
  digitalWrite( 9 , LOW );
  digitalWrite( 8 , HIGH );
  delay(500);
  digitalWrite( 8 , LOW );
  delay(500);
}*/
 if  ( distanceCm >= 60 )
{
  /* lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
  lcd.setCursor(10,0);
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("STATS:");
  lcd.setCursor(6,1);
  lcd.print("!!OK!!    ");*/
  digitalWrite( 8 , LOW );
  digitalWrite( 9 , HIGH );
  digitalWrite( 7 , LOW );
  digitalWrite( 12 , LOW );
}

else if (( distanceCm < 60 ) && ( distanceCm >= 40 ))
{
  /* lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
  lcd.setCursor(10,0);
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("STATS:");
  lcd.setCursor(6,1);
  lcd.print("!!OK!!     ");*/
  digitalWrite( 8 , LOW );
  digitalWrite( 12 , LOW );
 digitalWrite( 7 , LOW );
  digitalWrite( 9 , HIGH );
  delay(500);
  digitalWrite( 9 , LOW );
  delay(500);  
}
else if (( distanceCm < 40 ) && ( distanceCm >= 20 ))
{
   /*lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
  lcd.setCursor(10,0);
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("STATS:");
  lcd.setCursor(6,1);
  lcd.print("!!DANGER!!");*/
  digitalWrite( 8 , LOW );
  digitalWrite( 9 , LOW );
  digitalWrite( 12 , HIGH );
  digitalWrite( 7 , HIGH );
  delay( 500);
  digitalWrite( 7 , LOW );
  delay( 500);
  
}
else if ( distanceCm < 20 )
{
/*   lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
  lcd.setCursor(10,0);
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("STATS:");
  lcd.setCursor(6,1);
  lcd.print("!!DANGER!!");*/
  digitalWrite( 8 , LOW );
  digitalWrite( 9 , LOW );
  digitalWrite( 7 , HIGH );
 
  digitalWrite( 12 , HIGH );
  delay(500);
  digitalWrite( 12 , LOW );
  delay(500);
}
delay(1000);
}
