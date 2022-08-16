int in1 = 22;
int in2 = 23;
int pot = A7;
int sp = 30;
int x = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(sp, OUTPUT);
pinMode(pot, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
x = digitalRead(pot);
x = map(x, 0, 1023, 0, 255);
digitalWrite(sp, x);
digitalWrite(in1, 1);
digitalWrite(in2, 0);

}
