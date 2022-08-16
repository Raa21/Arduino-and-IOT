const int trigPin = 3;
const int echoPin = 4;
#define voice 6
int sensorPin = 2;
int sensorValue;
int limit = 300;
int IR = 8;
  long duration, distance;
//const int flamePin = 11;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(voice, OUTPUT);
//  pinMode(flamePin, INPUT);
  pinMode(5, OUTPUT);
  pinMode(IR, INPUT);//buzzer
}
void loop() {

  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
//distanceInch = duration*0.0133/2;
Serial.println( distance );
  digitalWrite(voice, LOW);
  digitalWrite(5, LOW);
  sensorValue = digitalRead(sensorPin);
  Serial.println("Analog Value : ");
  Serial.println(sensorValue);
  Serial.println("Distance : ");
  Serial.println(distance);
  Serial.println("IR : ");
   Serial.println(digitalRead(IR));
 // Flame = digitalRead(flamePin);
 

  if (distance < 20) 
  {
      digitalWrite(5, LOW);
      digitalWrite(voice, HIGH);
      delay(400); 
      digitalWrite(voice, LOW);
      delay(5000);
      
       if (( sensorValue == 0) && (digitalRead(IR) == 0))
  {
    digitalWrite(5, 1);
     delay(100);
  }
  else if (( sensorValue == 0) && (digitalRead(IR) == 1))
  {
    digitalWrite(5, 1);
     delay(100);
  }
  else if (( sensorValue == 1) && (digitalRead(IR) == 0))
  {
    digitalWrite(5, 1);
     delay(100);
  }
  else if (( sensorValue == 1) && (digitalRead(IR) == 1))
  {
    digitalWrite(5, 0);
     delay(100);
  }
  
  }
  else
  {
    digitalWrite(5, LOW);
    digitalWrite(voice, LOW);
      delay(100);
       if (( sensorValue == 0) && (digitalRead(IR) == 0))
  {
    digitalWrite(5, 1);
     delay(100);
  }
  else if (( sensorValue == 0) && (digitalRead(IR) == 1))
  {
    digitalWrite(5, 1);
     delay(100);
  }
  else if (( sensorValue == 1) && (digitalRead(IR) == 0))
  {
    digitalWrite(5, 1);
     delay(100);
  }
  else if (( sensorValue == 1) && (digitalRead(IR) == 1))
  {
    digitalWrite(5, 0);
     delay(100);
  }
  }
  delay(100);
}
