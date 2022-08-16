
#define redPin 9
#define greenPin 10
#define bluePin 11

void setup()
{
  //Serial setup
  Serial.begin(9600);
  Serial.println("-= HC-05 Bluetooth RGB LED =-");
  
 
  pinMode(4, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  digitalWrite(4,HIGH);

  setColor(255, 0, 0);
  delay(500);
  setColor(0, 255, 0);
  delay(500);
  setColor(0, 0, 255);
  delay(500);
  setColor(255, 255, 255);
}

void loop()
{
  while (Serial.available() > 0)
  {
    int redInt = Serial.parseInt();
    int greenInt = Serial.parseInt();
    int blueInt = Serial.parseInt();

    redInt = constrain((255-redInt), 0, 255);
    greenInt = constrain((255-greenInt), 0, 255);
    blueInt = constrain((255-blueInt), 0, 255);

    if (Serial.available() > 0)
    {
      setColor(redInt, greenInt, blueInt);

      Serial.print("Red: ");
      Serial.print(redInt);
      Serial.print(" Green: ");
      Serial.print(greenInt);
      Serial.print(" Blue: ");
      Serial.print(blueInt);
      Serial.println();

      Serial.flush();
    }
  }
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
