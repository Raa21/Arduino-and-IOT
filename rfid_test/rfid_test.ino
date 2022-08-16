#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

Servo myservo;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();  
  Serial.begin(9600);
 myservo.attach(3);
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.setCursor(0,0);
  lcd.print("Place your card");
  lcd.setCursor(0,1);
  lcd.print("on the reader...");
  myservo.write(0);
    

}
void loop() 
{
  lcd.setCursor(0,0);
  lcd.print("Place your card");
  lcd.setCursor(0,1);
  lcd.print("on the reader...");
   //Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if ((content.substring(1) == "42 B6 E0 1C")|| (content.substring(1) == "C6 60 BB 1D")) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.setCursor(0,0);
  lcd.print("   Authorized    ");
  lcd.setCursor(0,1);
  lcd.print("   !!!!Access!!!!    ");
    myservo.write(90);
    delay(4000);
    myservo.write(0);
     
  }
 
 else   {
    Serial.println(" Access denied");
    lcd.setCursor(0,0);
  lcd.print("   !!!!Access!!!!    ");
  lcd.setCursor(0,1);
  lcd.print("   !!!!Denied!!!!    ");
    myservo.write(0); 
    delay(2000);
    
  }
  delay(500);
}
