const int trigPin = 5;
const int echoPin = 7;
int x = 0;


long duration;
int distanceCm, distanceInch;

void setup() {
//lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(3, INPUT);
pinMode(6, OUTPUT);

digitalWrite(6, 0);
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

 x = digitalRead(3);
 Serial.println(x); 
if  (distanceCm < 20)
{
  digitalWrite(6, 1);
  delay(300);
  digitalWrite(6, 0);
  delay(5000);
}
 else if (distanceCm >= 20)
{
  digitalWrite(6, 0);
  delay(300);
}
 
/*else
{
  digitalWrite(6, 0);
  myservo.write(0);
  delay(300);
}*/


}
