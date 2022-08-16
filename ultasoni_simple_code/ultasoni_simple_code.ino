//#include<LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 3;
const int echoPin = 4;

long duration;
int distanceCm, distanceInch;

void setup() {
//lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
Serial.begin(9600);
/*lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);*/
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

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
Serial.println(distanceCm);
//Serial.println(distanceInch);


/*if(distanceCm < 100)
{
lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
lcd.print("Distance: "); // Prints string "Distance" on the LCD
lcd.print(distanceCm);// Prints the distance value from the sensor
lcd.print(" cm");
delay(10);
lcd.setCursor(0,1);
lcd.print("Distance: ");
lcd.print(distanceInch);
lcd.print(" inch");
delay(10);
}
else if(distanceCm > 100)
{
  lcd.clear();
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
lcd.print("out of range ");
delay(100);
  }*/
  delay(1000);
}
