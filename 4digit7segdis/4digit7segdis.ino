#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000


TM1637Display display(CLK, DIO);

void setup()
{
pinMode(5, INPUT);
}


void loop()
{

 int x = digitalRead(5);
  display.setBrightness(0x0f);
  if( x == 0)
{
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  display.setSegments(data);
  display.showNumberDec(23, false, 2,1);
  delay(TEST_DELAY);
  
  display.setSegments(data);
  display.showNumberDec(153, false, 3, 1);
  delay(TEST_DELAY);

  display.setSegments(data);
  for(int i=0; i<=20; i++)
  {
    display.showNumberDec(i);
    delay(1000);
  }

}
}
