

char str;
void setup() {
Serial.begin(9600);
  pinMode(9, OUTPUT);      // set Motor pins as output
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
    // put your setup code here, to run once:

}

void loop() {
 while(Serial.available())
 {
  str = Serial.read();
  if(str == 'F')
  {
    digitalWrite(12, LOW);      //movebackword         
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);                                
    digitalWrite(9, HIGH); // put your main code here, to run repeatedly:
  }
  else if (str == 'B')
  {
     digitalWrite(12, HIGH);      //movebackword         
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);                                
    digitalWrite(9, LOW);
  }
  else if (str == 'R')
  {
     digitalWrite(12, LOW);      //movebackword         
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);                                
    digitalWrite(9, LOW);
  }
  else if (str == 'L')
  {
     digitalWrite(12, HIGH);      //movebackword         
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);                                
    digitalWrite(9, HIGH);
  }
  else if (str == 'S')
  {
     digitalWrite(12, LOW);      //movebackword         
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);                                
    digitalWrite(9, LOW);
  }
 }

}
