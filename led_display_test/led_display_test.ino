#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS
#define MAX_DEVICES  1

MD_Parola p = MD_Parola(CS_PIN,MAX_DEVICES);

void setup()
{
  p.begin();
}

void loop()
{
  p.print("1234");
}
