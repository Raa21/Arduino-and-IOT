int x;
void setup() {
  // put your setup code here, to run once:
pinMode(3, INPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 x = digitalRead(3);
 if ( x == 1)
 {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW); 
  
 }
 else if (x == 0)
 {
  digitalWrite(4, HIGH );
  digitalWrite(5, HIGH);
  delay(10000);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW); 
 }
 delay(500);
}
