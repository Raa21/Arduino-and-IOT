#define x A0 // x_out pin of Accelerometer
#define y A1 // y_out pin of Accelerometer
#define z A2 // z_out pin of Accelerometer
 
/*variables*/
int xsample=0;
int ysample=0;
int zsample=0;
long start;
int buz=0;
 
/*Macros*/
#define samples 50
#define maxVal 20 // max change limit
#define minVal -20 // min change limit
#define buzTime 5000 // buzzer on time
 
void setup()
{

Serial.begin(9600); // initializing serial

Serial.print("EarthQuake Detector ");

Serial.println("Calibrating.....");

Serial.println("Please wait...");


for(int i=0;i<samples;i++) // taking samples for calibration
{
xsample+=analogRead(x);
ysample+=analogRead(y);
zsample+=analogRead(z);
}
 
xsample/=samples; // taking avg for x
ysample/=samples; // taking avg for y
zsample/=samples; // taking avg for z
 
delay(3000);

Serial.println("Calibrated");
Serial.println("Device Ready");
delay(1000);

}
 
void loop()
{
int value1=analogRead(x); // reading x out
int value2=analogRead(y); //reading y out
int value3=analogRead(z); //reading z out
 
int xValue=xsample-value1; // finding change in x
int yValue=ysample-value2; // finding change in y
int zValue=zsample-value3; // finding change in z
 
/*displying change in x,y and z axis values over lcd*/

Serial.println(xValue);
Serial.write(xValue);

Serial.println(yValue);
Serial.write(yValue);

Serial.println(zValue);
Serial.write(zValue);
delay(100);
}
