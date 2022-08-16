#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial sgps(4, 5);

void setup()
{
  Serial.begin(115200);
  sgps.begin(9600);
}

void loop()
{
  if (sgps.available())
  {
    int c = sgps.read();
    if (gps.encode(c))
    {
float slat,slon;
      gps.f_get_position(&slat, &slon);
      Serial.print("Latitude :");
      Serial.println(slat, 6);
      Serial.print("Longitude:");
      Serial.println(slon, 6);
      delay(1000);
    }
  }
  else
  {
      Serial.println("No Satellites found!!!");
      delay(1000);
  }
}
