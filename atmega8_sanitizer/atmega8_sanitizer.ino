
int trig = 1; // attach pin 3 to Trig
int echo = 2; //attach pin 4 to Echo
//int gnd = 5; //attach pin 5 to GND
int led = 9;
int t1 = A2;
int t2 = A3;
int t3 = A4;
int t4 = A5;

int a = 0;
int b = 0;
int c = 0;
int d = 0;
int dt = 0;

int motor = 8;
void setup() {
  
 pinMode (led, OUTPUT);
   pinMode (trig, OUTPUT);
  pinMode (motor, OUTPUT);
  pinMode (echo, INPUT);
  pinMode (t1, INPUT);
  pinMode (t2, INPUT);
  pinMode (t3, INPUT);
  pinMode (t4, INPUT);

  // initialize serial communication:
 
  digitalWrite(motor, LOW);
    digitalWrite(led, LOW);
}
void loop()
{
  //digitalWrite(vcc, HIGH);                    // establish variables for duration of the ping,and the distance result in inches and centimeters:
  long duration, inches, cm;                  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);                        // The same pin is used to read the signal from the PING))): a HIGH, pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  duration = pulseIn(echo, HIGH);                 // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  /*Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();*/
  int x = analogRead(A2);
  int y = analogRead(A3);
  int z = analogRead(A4);
  int w = analogRead(A5);
  
 /* Serial.print("x: ");
  Serial.print(x);
  Serial.print("y: ");
  Serial.print(y);
  Serial.print("z: ");
  Serial.print(z);
  Serial.print("w: ");
  Serial.print(w);*/
  
  
  if (cm < 10)  {
    digitalWrite(motor, HIGH);
     digitalWrite(led, HIGH);//on
    if (x > 900)
    {
      a = 5000;
    }
    else  if (y > 900)
    {
      b = 5000;
    }
    else  if (z > 900)
    {
      c = 5000;
    }
     else  if (w > 900)
    {
     d = 5000;
    }
    else if (x == 0)
    {
      a = 0;
    }
    else  if (y == 0)
    {
      b = 0;
    }
    else  if (z == 0)
    {
      c = 0;
    }
     else  if (w == 0)
    {
     d = 0;
    }
     dt = a+b+c+d;
    delay(dt);
    digitalWrite(motor, LOW);
     digitalWrite(led, LOW); 
    delay(3000);
    

  }
  else {
    digitalWrite(motor, LOW);
    digitalWrite(led, LOW);//off
  }
}
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
