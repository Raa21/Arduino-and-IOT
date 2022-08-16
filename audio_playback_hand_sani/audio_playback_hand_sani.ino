const int trigPin = 5;
const int echoPin = 7;

long duration;
int distanceCm, distanceInch;

void setup() {
//lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(6, OUTPUT);
digitalWrite(2, 0);
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


if(distanceCm < 30)
{
  digitalWrite(6, HIGH);
  delay(300);
  digitalWrite(6, LOW);
  delay(300);
}
else
{
  digitalWrite(6, LOW);
  delay(100);
}
}
