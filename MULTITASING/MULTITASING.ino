#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12



unsigned long previousTimeLed1 = millis();
unsigned long previousTimeLed2 = millis();
long timeIntervalLed1 = 3000;
long timeIntervalLed2 = 2000;
int ledState1 = HIGH;
int ledState2 = HIGH;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, INPUT);
  pinMode(LED_4_PIN, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  /* task 1
  if(currentTime - previousTimeLed1 > timeIntervalLed1) {
    previousTimeLed1 = currentTime;

    if (ledState1 == HIGH) {
      ledState1 = LOW;
    }
    else {
      ledState1 = HIGH;
    }

    digitalWrite(LED_1_PIN, ledState1);
  }

  // task 2
  if (Serial.available()) {
    int userInput = Serial.parseInt();
    if (userInput >= 0 && userInput < 256) {
      analogWrite(LED_2_PIN, userInput);
    }
  }*/

  // task 3
 if(currentTime - previousTimeLed1 > timeIntervalLed1) 
 {
    previousTimeLed1 = currentTime;
  if (digitalRead(LED_3_PIN) == HIGH) {
     digitalWrite(LED_1_PIN, !HIGH);
       
  }
}
  else {
    digitalWrite(LED_1_PIN, !LOW);
  }
  if(currentTime - previousTimeLed2 > timeIntervalLed2) 
  {
    previousTimeLed2 = currentTime;
   if (digitalRead(LED_4_PIN) == HIGH) {
     digitalWrite(LED_2_PIN, !HIGH);
       
  }
  }
  else {
    digitalWrite(LED_2_PIN, !LOW);
  }
  
  /*task 4
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  if (potentiometerValue > 512) {
    digitalWrite(LED_4_PIN, HIGH);
  }
  else {
    digitalWrite(LED_4_PIN, LOW);
  }

  // task 5
  if (currentTime - previousTimeSerialPrintPotentiometer > timeIntervalSerialPrint) {
    previousTimeSerialPrintPotentiometer = currentTime;
    Serial.print("Value : ");
    Serial.println(potentiometerValue);
  }*/
}
