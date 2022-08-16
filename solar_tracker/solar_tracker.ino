#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 20;

/*Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 20;*/
//Assigning LDRs
//int ldrtopl = 2; //top left LDR green
int ldrtopr = A1; //top right LDR yellow
//int ldrbotl = 3; // bottom left LDR blue
int ldrbotr = A0; // bottom right LDR orange

 void setup () 
 {
  Serial.begin(9600);
  servohori.attach(11);
  servohori.write(0);
 /* servoverti.attach(9);
  servoverti.write(0);*/
  delay(500);
 }

void loop()
{
  servoh = servohori.read();
 // servov = servoverti.read();
  //capturing analog values of each LDR
  //int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  //int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  int x = digitalRead(9);
  
  // calculating average
 /* int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

  if (topr < botr)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (botr < topr)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }*/
  
   if ((topr > botr) && (x == 0))
  {
    servohori.write(servoh +5);
    Serial.println("Increasing");
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(500);
  }
  else if ((botr > topr) && (x == 0))
  {
    servohori.write(servoh);
    Serial.println("Stop");
    delay(500);
  }
  else if (x == 1)
  {
    Serial.println("decending");
     servohori.write(120);
      delay(100);
     servohori.write(100);
      delay(100);
     servohori.write(80);
      delay(100);
     servohori.write(60);
      delay(100);
     servohori.write(40);
    delay(100);
     servohori.write(20);
    delay(500);
  }
 
  delay(500);
}
