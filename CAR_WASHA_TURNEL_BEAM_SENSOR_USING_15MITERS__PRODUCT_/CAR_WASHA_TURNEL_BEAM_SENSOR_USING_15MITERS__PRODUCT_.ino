int LED = 5; 
int isObstaclePin = 3;  
int isObstacle = HIGH;  
int let;
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
}
void loop() {
  isObstacle = digitalRead(isObstaclePin);
  if ((isObstacle == LOW)&& (let == 0))
  {
    Serial.println("clear");
    digitalWrite(LED, HIGH);
    delay(5000);//3sec in gift clg
    digitalWrite(LED, LOW); //off
    // delay(3000);
     let = 1;
  }
 /* else if (isObstacle == LOW)
  {
    let = 0;
  }*/
  else
  {
    let = 0;
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, LOW);
  }
  //delay(10000);
}
