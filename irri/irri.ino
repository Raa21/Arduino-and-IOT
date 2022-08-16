int x = A0;

int motor = 6; 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(x, INPUT);
pinMode(motor, OUTPUT);
digitalWrite(motor, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
int y = analogRead(x);
y = map(y, 0, 1023, 100, 0);
 while(Serial.available())
 {
  char c = Serial.read();
  
   if( c == 'A')
  {
  digitalWrite(motor, HIGH);
  }
  else if( c == 'a')
  {
  digitalWrite(motor, LOW);
 }
 
else{
  digitalWrite(motor, LOW);
}
 }
delay(500);
}
