int ob1 = 3;
int ob2 = 4;
int led = 5;
int voice = 6;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(3, INPUT);
pinMode(4, INPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
digitalWrite(5, 0);
digitalWrite(6, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
int x = digitalRead(3);
int y = digitalRead(4);

if ( (x == 0) || (y == 0) )
{
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  delay(300);
  digitalWrite(6, 0);
  delay(300);
   digitalWrite(6, 1);
  delay(300);
  digitalWrite(6, 0);
  delay(300);
}
else if ( (x == 0) && (y == 0) )
{
  digitalWrite(5, 1);
 digitalWrite(6, 1);
  delay(300);
  digitalWrite(6, 0);
  delay(300);
   digitalWrite(6, 1);
  delay(300);
  digitalWrite(6, 0);
  delay(300);
}
else
{
   digitalWrite(5, 0);
  digitalWrite(6, 0);
}
delay(2000);
}
