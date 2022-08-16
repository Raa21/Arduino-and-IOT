
String str;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(30);
  String t; 
  while(Serial.available())
  { 
    t += (char)Serial.read(); 
    Serial.println(t);
    
  if(t.length() > 0)
  {
    if (t == "reg")
    {
      Serial.println("Registration");
      delay(1000);
    }
    else if (t == "del")
    {
      Serial.println("Deletion");
      delay(1000);
    }
    else 
    {
      Serial.println("Enter correct code");
      delay(100);
    }
  }
  }
  Serial.println("Checking");
  delay(1000);
}
