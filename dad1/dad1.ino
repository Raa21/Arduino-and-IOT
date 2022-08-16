int moistPin = A1;
int pump = 3;
void setup() {
  // put your setup code here, to run once:
pinMode( moistPin, INPUT);
pinMode( pump, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int value = analogRead(moistPin);
long soil_moist = map(value, 0, 750, 0, 100);
Serial.println(soil_moist);
if( soil_moist > 50 && soil_moist <100)
{
  digitalWrite( pump, HIGH);
}
else
{
  digitalWrite( pump, LOW);
}
delay(200); 
}
