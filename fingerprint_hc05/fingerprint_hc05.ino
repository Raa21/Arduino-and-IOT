#include <DFRobot_ID809_I2C.h>
#include <Servo.h>

Servo myservo; 
#define COLLECT_NUMBER 3  //Fingerprint sampling times, can be set to 2-3

DFRobot_ID809_I2C fingerprint;
//String desc;

void setup(){
  /*Init print serial port */
  Serial.begin(9600);
  myservo.attach(9);
  /*Take FPSerial as communication port of the module*/
  fingerprint.begin();
  /*Wait for Serial to open*/
  while(!Serial);
  /*Test whether the device can communicate properly with mainboard 
    Return true or false
    */
  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    /*Get error code information*/
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
    delay(1000);
  }
}

void loop ()
{
  myservo.write(0);
   fingerprintMatching();

   while(Serial.available()) {
delay(10);
char voice =Serial.read();
Serial.println(voice);

if ((voice == 'A') || (voice == 'a') )
{
  Serial.println("Enter Settings mode");
  
  
 if ((voice == 'B') || (voice == 'b') )
{
  Serial.println("Enter fingerprint registration mode");
  fingerprintRegistration();
}

else if ((voice == 'C') || (voice == 'c') )
{
  Serial.println("Enter fingerprint deletion mode");
  fingerprintDeletion();
}
else
{
  Serial.println("Enter a valid Code");
}
}
else
{
  Serial.println("Enter a valid Code to Enter Settings");
}
   }
delay(300);
}
//Compare fingerprints
void fingerprintMatching(){
  /*Compare the captured fingerprint with all fingerprints in the fingerprint library
    Return fingerprint ID number(1-80) if succeed, return 0 when failed
   */
  uint8_t ret = 0;
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  Serial.println("Please press down your finger");
  /*Capture fingerprint image, 10s idle timeout 
    If succeed return 0, otherwise return ERR_ID809
   */
  if((fingerprint.collectionFingerprint(/*timeout=*/10)) != ERR_ID809){
    /*Set fingerprint LED ring to quick blink in yellow 3 times*/
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
    Serial.println("Capturing succeeds");
  }else{
    Serial.println("Capturing fails");
    /*Get error code information*/
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
  }
  Serial.println("Please release your finger");
  /*Wait for finger to release
    Return 1 when finger is detected, otherwise return 0 
   */
  while(fingerprint.detectFinger());
  
  /*Compare the captured fingerprint with all the fingerprints in the fingerprint library 
    Return fingerprint ID(1-80) if succeed, return 0 when failed 
   */
  ret = fingerprint.search();
  /*Compare the captured fingerprint with a fingerprint of specific ID 
    Return fingerprint ID(1-80) if succeed, return 0 when failed 
   */
  //ret = fingerprint.verify(/*Fingerprint ID = */1);  
  if(ret != 0){
    /*Set fingerprint LED ring to always ON in green */
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
    Serial.print("Matching succeeds,ID=");
    Serial.println(ret);
    myservo.write(90); 
    delay(2000);
    myservo.write(0);
  }
  else{
    /*Set fingerprint LED ring to always ON in red*/
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
    Serial.println("Matching fails");
  }
  Serial.println("-----------------------------");
  myservo.write(0);
  delay(1000);
}

//Fingerprint Registration
void fingerprintRegistration(){
  uint8_t ID,i;
  /*Compare the captured fingerprint with all fingerprints in the fingerprint library
    Return fingerprint ID number(1-80) if succeed, return 0 when failed
    Function: clear the last captured fingerprint image
   */
  fingerprint.search();       //Can add "if else" statement to judge whether the fingerprint has been registered. 
  /*Get a unregistered ID for saving fingerprint 
    Return ID number when succeed 
    Return ERR_ID809 if failed
   */
  if((ID = fingerprint.getEmptyID()) == ERR_ID809){
    while(1){
      /*Get error code imformation*/
      //desc = fingerprint.getErrorDescription();
      //Serial.println(desc);
      delay(1000);
    }
  }
  Serial.print("Unregistered ID,ID=");
  Serial.println(ID);
  i = 0;   //Clear sampling times 
  /*Fingerprint Sampling 3 times */
  while(i < COLLECT_NUMBER){
    /*Set fingerprint LED ring to breathing lighting in blue*/
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
    Serial.print("The fingerprint sampling of the");
    Serial.print(i+1);
    Serial.println("(th) time is being taken");
    Serial.println("Please press down your finger");
    /*Capture fingerprint image, 10s idle timeout 
      If succeed return 0, otherwise return ERR_ID809
     */
    if((fingerprint.collectionFingerprint(/*timeout = */10)) != ERR_ID809){
      /*Set fingerprint LED ring to quick blink in yellow 3 times*/
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
      Serial.println("Capturing succeeds");
      i++;   //Sampling times +1 
    }else{
      Serial.println("Capturing fails");
      /*Get error code information*/
      //desc = fingerprint.getErrorDescription();
      //Serial.println(desc);
    }
    Serial.println("Please release your finger");
    /*Wait for finger to release
      Return 1 when finger is detected, otherwise return 0 
     */
    while(fingerprint.detectFinger());
  }

  /*Save fingerprint information into an unregistered ID*/
  if(fingerprint.storeFingerprint(/*Empty ID = */ID) != ERR_ID809){
    Serial.print("Saving succeed,ID=");
    Serial.println(ID);
    /*Set fingerprint LED ring to always ON in green*/
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
    delay(1000);
    /*Turn off fingerprint LED ring */
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eNormalClose, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  }else{
    Serial.println("Saving failed");
    /*Get error code information*/
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
  }
  Serial.println("-----------------------------");
}


//Fingerprint deletion
void fingerprintDeletion(){
  uint8_t ret = 0;
  Serial.println("Press your finger on the sensor to delete the fingerprint");
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  /*Capture fingerprint image, 10s idle timeout 
    If succeed return 0, otherwise return ERR_ID809
   */
  if((fingerprint.collectionFingerprint(/*timeout=*/10)) != ERR_ID809){
    /*Compare the captured fingerprint with all the fingerprints in the fingerprint library 
      Return fingerprint ID(1-80) if succeed, return 0 when failed 
     */
    ret = fingerprint.search();
    if(ret != 0){
      /*Delete the fingerprint of this ID*/
      fingerprint.delFingerprint(/*Fingerprint ID = */ret);
      //fingerprint.delFingerprint(DELALL);  //Delete all fingerprints 
      Serial.print("delete succeeds,ID=");
      Serial.println(ret);
      /*Set fingerprint LED ring to always ON in green */
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
    }else{
      Serial.println("Fingerprint is unregistered");
      /*Set fingerprint LED ring to always ON in red*/
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
    }
  }else{
    Serial.println("Capturing fails");
    /*Get error code information*/
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
    /*Set fingerprint LED ring to always ON in red*/
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
  }
  Serial.println("Please release your finger");
  /*Wait for finger to release
    Return 1 when finger is detected, otherwise return 0 
   */
  while(fingerprint.detectFinger());
    /*Check whether the fingerprint ID has been registered 
    Return 1 if registered, otherwise return 0 
   */
//  if(fingerprint.getStatusID(/*Fingerprint ID = */ret)){
//    Serial.println("ID has been registered");
//  }else{
//    Serial.println("ID is unregistered");
//  }
  Serial.println("-----------------------------");
  delay(1000);
}
