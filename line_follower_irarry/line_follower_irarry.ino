
int revleft4 = 9;       //REVerse motion of Left motor
int fwdleft5 = 10;       //ForWarD motion of Left motor
int revright6 = 11;      //REVerse motion of Right motor
int fwdright7 = 12; 
int s1 = 2;
int s2 = 3;
int s3 = 4;
int s4 = 5;
int s5 = 6;
void setup() {
Serial.begin(9600);
  pinMode(revleft4, OUTPUT);      // set Motor pins as output
  pinMode(fwdleft5, OUTPUT);
  pinMode(revright6, OUTPUT);
  pinMode(fwdright7, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
 
  
    // put your setup code here, to run once:

}

void loop() {
 int x = digitalRead(s1);
 int y = digitalRead(s2);
 int z = digitalRead(s3);
 int a = digitalRead(s4);
 int b = digitalRead(s5);
  if((x == 1) && (y == 1) && (z == 1) && (a == 1) && (b == 1))
  {
     fwd();
     Serial.println("Forward");// put your main code here, to run repeatedly:
  }
  else if ((x == 0) || (y == 0))
  {
     stp();
     delay(500);
     right();
     Serial.println("Right");
  }
  else if ((a == 0) || (b == 0))
  {
     stp();
     delay(500);
     left();
     Serial.println("left");
  }
  else if (z == 0)
  {
    stp();
    delay(500);
    bck();
    delay(200);
    right();
    Serial.println("back");
    
  }

}
void fwd()
{
  digitalWrite(fwdright7, LOW);      //movebackword         
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, HIGH);
}
void bck()
{
  digitalWrite(fwdright7, HIGH);      //movebackword         
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);                                
    digitalWrite(revleft4, LOW);
}
void right()
{
  digitalWrite(fwdright7, LOW);      //movebackword         
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, HIGH);                                
    digitalWrite(revleft4, LOW);
}
void left()
{
   digitalWrite(fwdright7, HIGH);      //movebackword         
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, HIGH);
}
void stp()
{
  digitalWrite(fwdright7, LOW);      //movebackword         
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
}
