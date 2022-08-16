int pirOutput= 5;
void setup()
{
  Serial.begin(9600);
  /*pinMode(LED1,OUTPUT);
  pinMode(GND1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(GND2,OUTPUT);*/
  pinMode(pirOutput,INPUT);
 pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  //digitalWrite(pirOutput,LOW);
  /*digitalWrite(GND1,LOW);
  digitalWrite(GND2,LOW);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);*/
  
  //delay(15000);
  //digitalWrite(LED1,HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
void loop()
{
  Serial.println(digitalRead(pirOutput));
  if(digitalRead(pirOutput)== 0)
  {
    //digitalWrite(LED2,HIGH);
    Serial.println("OK");
    digitalWrite(6, LOW);
    digitalWrite(7, !LOW);
    delay(3000);
    digitalWrite(7, LOW);
  }
 else
 {
  digitalWrite(6, !LOW);
 }
 delay(1000);
}
