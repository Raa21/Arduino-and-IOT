//YouTube|Tech at Home

int in1 = 2;
int in2 = 3;
int in3 = 8;
int in4 = 7;
//int enable1 = 5;  // pin with ~ symbol

int channel_2 = 10;  // pin with ~ symbol
int channel_1 = 11;  // pin with ~ symbol
void setup()
{
  pinMode(channel_2, INPUT);
  pinMode(channel_1, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //pinMode(enable1, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int pwm = 0;
  int value = pulseIn(channel_2, HIGH);
  int valueS = pulseIn(channel_1, HIGH);
  // Serial.println(value);
  delay(100);
  Serial.println(valueS);
  
  Serial.println(value);
  
  if ((value >= 1400)&& (value <= 1600) && (valueS >= 1400)&& (valueS <= 1600) )
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    // analogWrite(enable1, 0);
  }

  else if ((valueS > 990)&&(valueS < 2000)&& (value > 1400)&& (value < 1600)) 
  {
    if ((valueS > 1600)&&(valueS < 2000))
    {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW); //FORWARD
    digitalWrite(in4, HIGH);
    }
    else if ((valueS > 1000)&&(valueS < 1400))
    {
      digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    }
    
  }
  else if ((valueS > 1400)&&(valueS < 1600)&& (value > 990)&& (value < 2000)) 
 {
  if((value > 990)&& (value < 1400))
  {
  

      digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if ((value > 1600)&& (value < 2000))
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH); //FORWARD
    digitalWrite(in4, LOW);

   
    //analogWrite(enable1, 0);
  }
 }
  delay(10);
}
