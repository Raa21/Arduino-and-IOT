
const int trigPin = 3;
const int echoPin = 4;
const int trigPin1 = 5;
const int echoPin1 = 6;
int buzzer =9;

long duration;
int distanceCm, distanceInch;
long duration1;
int distanceCm1, distanceInch1;

void setup() {

Serial.begin(9600);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(buzzer, OUTPUT);

digitalWrite(buzzer, LOW);
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


digitalWrite(trigPin1, LOW);
delayMicroseconds(2);

digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);

duration1 = pulseIn(echoPin1, HIGH);
distanceCm1= duration1*0.034/2;
distanceInch1 = duration1*0.0133/2;
Serial.println(distanceCm1);

if((distanceCm < 5) && (distanceCm1 < 5))
{
  digitalWrite(buzzer, HIGH);
  delay(100);
    digitalWrite(buzzer, LOW);
  delay(100);
  
}
else if((distanceCm > 5) && (distanceCm1 < 5))
{
  digitalWrite(buzzer, HIGH);
  delay(350);
    digitalWrite(buzzer, LOW);
  delay(350);
  
}
else if((distanceCm < 5) && (distanceCm1 > 5))
{
  digitalWrite(buzzer, HIGH);
  delay(550);
    digitalWrite(buzzer, LOW);
  delay(550);
  
}
else if((distanceCm > 5) && (distanceCm1 > 5))
{
  
    digitalWrite(buzzer, LOW);
  delay(10);
  
}
  delay(1);
}
