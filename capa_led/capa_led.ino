int x = 0;
void setup() {
Serial.begin(9600);
pinMode(3, INPUT);
pinMode(4, OUTPUT);
/*pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);// put your setup code here, to run once:*/
digitalWrite(4, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
x = digitalRead(3);
if( x == 1 )
{
  digitalWrite(4, 1);
  delay(3000);
  digitalWrite(4, 0);
  
 /* digitalWrite(5, 1);
  delay(300);
  digitalWrite(5, 0);
  
  digitalWrite(6, 1);
  delay(300);
  digitalWrite(6, 0);
  
  digitalWrite(7, 1);
  delay(300);
  digitalWrite(7, 0);
 
  digitalWrite(8, 1);
  delay(300);
  digitalWrite(8, 0);
  
  digitalWrite(9, 1);
  delay(300);
  digitalWrite(9, 0);
  
  digitalWrite(10, 1);
  delay(300);
  digitalWrite(10, 0);
  
  digitalWrite(11, 1);
  delay(300);
  digitalWrite(11, 0);*/
  
  
}
else
{
  /*digitalWrite(4, 1);
  delay(300);
 
  
  digitalWrite(5, 1);
  delay(300);
  
  
  digitalWrite(6, 1);
  delay(300);
 
  
  digitalWrite(7, 1);
  delay(300);
 
 
  digitalWrite(8, 1);
  delay(300);
 
  
  digitalWrite(9, 1);
  delay(300);
  
  
  digitalWrite(10, 1);
  delay(300);
  

  digitalWrite(11, 1);
  delay(300);*/
   digitalWrite(4, 0);
   /*digitalWrite(5, 0);
   digitalWrite(6, 0);
   digitalWrite(7, 0);
   digitalWrite(8, 0);
   digitalWrite(9, 0);
   digitalWrite(10, 0);
  digitalWrite(11, 0);*/
  
}
}
