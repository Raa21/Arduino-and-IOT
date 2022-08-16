
int trig = 3; // attach pin 3 to Trig
int echo = 4; //attach pin 4 to Echo

int let;
int count = 0;
int motor = 5;

long duration;
long cm = 0; 

void setup() 
{
  
  pinMode (5, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  digitalWrite(motor, LOW);
 //M pinMode(A0 , INPUT);
  

  // initialize serial communication:
  Serial.begin(9600);
}
void loop()
{
  //digitalWrite(vcc, HIGH);                    // establish variables for duration of the ping,and the distance result in inches and centimeters:
                   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  //Serial.println("ultasonic trig low");
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  //Serial.println("ultasonic trig HIGH");
  digitalWrite(trig, LOW); 
  //Serial.println("ultasonic trig low");// The same pin is used to read the signal from the PING))): a HIGH, pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  duration = pulseIn(echo, HIGH);                 // convert the time into a distance

  cm = microsecondsToCentimeters(duration);

 
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);

  
  if (cm < 60) 
  {
    Serial.println("condiion ok ");
//delay(1000);
             
    digitalWrite(motor, HIGH);
    Serial.println("motor on  ");
    
    
  }
  else 
  {
    
    digitalWrite(motor, LOW); //off
  }
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
