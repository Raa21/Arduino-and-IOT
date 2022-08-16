int motor_input1 = 12;
int motor_input2 = 11;
int motor_input3 = 10;
int motor_input4 = 9;
int RS = 0;
int LS = 0;
String voice;
void setup()
{
  Serial.begin(9600);
  pinMode(motor_input1, OUTPUT);   //RIGHT MOTOR
  pinMode(motor_input2, OUTPUT);   //RIGHT MOTOR
  pinMode(motor_input3, OUTPUT);   //LEFT MOTOR
  pinMode(motor_input4, OUTPUT); 
  pinMode(2, INPUT);

  pinMode(3, INPUT);//LEFT MOTOR
}

void loop()
{
  
  if (Serial.available())
  {
    voice = Serial.readString();
    
      if (voice == "left")
      {
        left();
      }
      else if (voice == "right")
      {
        right();
      }
      else if (voice == "back")
      {
        backward();
      }
       else if (voice == "forward") 
       {
         digitalWrite(motor_input1, HIGH);
        digitalWrite(motor_input2, LOW);
        digitalWrite(motor_input3, LOW);
        digitalWrite(motor_input4, HIGH);
        follow();
       }
       else if (voice == "stop")
       {
          digitalWrite(motor_input1, LOW);
          digitalWrite(motor_input2, LOW);
          digitalWrite(motor_input3, LOW);
          digitalWrite(motor_input4, LOW);
          
       }
    
  }
}



void backward(){ //backword
      digitalWrite(motor_input1, LOW);
      digitalWrite(motor_input2, HIGH);
      digitalWrite(motor_input3, HIGH);
      digitalWrite(motor_input4, LOW);
     
}

void left(){ //turnRight
      digitalWrite(motor_input1, HIGH);
      digitalWrite(motor_input2, LOW);
      digitalWrite(motor_input3, HIGH);
      digitalWrite(motor_input4, LOW);
      
}

void right(){ //turnLeft
      digitalWrite(motor_input1, LOW);
      digitalWrite(motor_input2, HIGH);
      digitalWrite(motor_input3, LOW);
      digitalWrite(motor_input4, HIGH);
      
}


void follow()
{
       RS = digitalRead(3);
      LS = digitalRead(2);
      //if Right Sensor and Left Sensor are at White color then it will call forword function
       if( (RS == 1) && (LS == 0)){right();}//if Right Sensor is Black and Left Sensor is White then it will call turn Right function  
       else if( (RS == 0) && (LS == 1)){left();} //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
      else
      {
        digitalWrite(motor_input1, HIGH);
      digitalWrite(motor_input2, LOW);
      digitalWrite(motor_input3, LOW);
      digitalWrite(motor_input4, HIGH);
     
      }  
  
}
