#include "HX711.h"

HX711 scale(2, 0);

float weight;
float calibration_factor = -109525.00; // for me this vlaue works just perfect 419640
 
void setup() 
{
  Serial.begin(115200);
 // pinMode(rbutton, INPUT_PULLUP); 
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average();
  }
  void loop() 
 
{
 
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
 
  weight = scale.get_units(5); 

    Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" KG");
  Serial.println();
  delay(1500);        // thingspeak needs minimum 15 sec delay between updates.
 
}
