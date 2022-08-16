int x;
int let = 0;
void setup() 
{
  pinMode(3, INPUT);
  pinMode(5, OUTPUT);// put your setup code here, to run once:
  digitalWrite(5, 0);
}

void loop() 
{
  x = digitalRead(3);
  if (x == 1) 
  {
    digitalWrite(5, 1);
    for(int i = 0; i < 100; i++)
    {
      delay(100);
    }
    digitalWrite(5, 0);
    // put your main code here, to run repeatedly:
  }
 
 else
 {
  digitalWrite(5, 0);
 }
 delay(1000);
}
