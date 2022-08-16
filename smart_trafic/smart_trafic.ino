void setup() {
 pinMode(5, INPUT);
pinMode(6, INPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);//RED
pinMode(9, OUTPUT);//GREEN
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);//RED
pinMode(12, OUTPUT); // put your setup code here, to run once:

}

void loop() {
  int x = digitalRead(5);
  int y = digitalRead(6);
   if( (x == 1) && (y == 0))
   {
    for( int i=0; i<10 ; i++)
    {
    digitalWrite(10, 1);
    digitalWrite(11, 1);
    digitalWrite(12, 0);
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
    delay(1000);
    }
    // put your main code here, to run repeatedly:
   }
   else if( (x == 0) && (y == 1))
   {
    for( int i=0; i<10 ; i++)
    {
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    digitalWrite(12, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(9, 0);
    delay(1000);
    }// put your main code here, to run repeatedly:
   }
   else if( (x == 0) && (y == 0))
   {
    
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    digitalWrite(12, 1);
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
    delay(1000);
    // put your main code here, to run repeatedly:
   }
   else if( (x == 1) && (y == 1))
   {
    return;
    // put your main code here, to run repeatedly:
   }

}
