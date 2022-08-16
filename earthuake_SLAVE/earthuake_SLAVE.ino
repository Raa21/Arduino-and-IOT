void setup() {
 Serial.begin(9600); // put your setup code here, to run once:

}

void loop() {
 
  char x = Serial.read();
  Serial.println(x);// put your main code here, to run repeatedly:
 

}
