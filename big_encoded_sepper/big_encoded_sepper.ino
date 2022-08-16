const int dir = 6;
const int ste = 7;

const int step_per_rev = 20000;

void setup() {
  // put your setup code here, to run once:
pinMode(dir, OUTPUT);
pinMode(ste, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(dir, HIGH);

for( int i=0; i < step_per_rev; i++)
{
  digitalWrite(ste ,HIGH);
  delayMicroseconds(60);
  digitalWrite(ste ,LOW);
  delayMicroseconds(60);
}
delay(1000);
/*digitalWrite(dir, LOW);

for( int i=0; i < (step_per_rev*2); i++)
{
  digitalWrite(ste ,HIGH);
  delayMicroseconds(1000);
  digitalWrite(ste ,LOW);
  delayMicroseconds(1000);
}
delay(1000);*/
}
