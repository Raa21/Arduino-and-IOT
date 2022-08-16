char c;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(A0, INPUT);
}

void loop() {
  int x  = analogRead(A0);
  x = map(x, 0, 1023, 0, 255);
  Serial.println(x);
  analogWrite(11, x);
 if (Serial.available())
 {
  c = Serial.read();
  Serial.println(c);
  if ( (c == 'L') ||  (c == 'B'))
  {
   // analogWrite(11, x);
    digitalWrite(9, 1);
    digitalWrite(10, 0);
  }
  else if  (c == 'R') 
  {
    //analogWrite(11, x);
    digitalWrite(9, 0);
    digitalWrite(10, 1);
  }
  else if (c == 'b')
  {
    //analogWrite(11, x);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
  }
 }

}
