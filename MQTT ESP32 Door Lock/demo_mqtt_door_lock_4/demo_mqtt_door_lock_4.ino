#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  

int signalPin = 23;

#define P_Lenght 5 // Give enough room for six chars + NULL char
#define U_Lenght 5

char Data1[P_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Data[U_Lenght];


byte data_count = 0, master_count = 0;

//bool Pass_is_good;

char customKey;

const byte ROWS = 4;

const byte COLS = 4;

char hexakeys[ROWS][COLS] = {

  {'1', '2', '3','A'},

  {'4', '5', '6','B'},

  {'7', '8', '9','C'},

  {'*', '0', '#','D'}

};
int us = 0;
int door = 1;
int count = 0;
String doorStat = "Closed";
byte rowPins[ROWS] = {32, 33, 27, 14}; //connect to the row pinouts of the keypad

byte colPins[COLS] = {16, 4, 2, 15}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad


// Replace the next variables with your SSID/Password combination
const char* ssid = "SVTRAPTOR";
const char* password = "1234567809";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "20.205.208.135";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

String device_id = "2";
String school_name = "XYZSchool";
String school_id = "2";
//String deviceStat="DoorStat";
String topic = device_id + "/" + school_id + "/" + school_name;
String sub = topic + "/" + "Ping_POST";
String sub1 = topic + "/" + "Reset_POST";
String sub2 = topic + "/" + "POST";

void setup() {
  Serial.begin(115200);
  lcd.begin();                     
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
  pinMode(35, INPUT);
  pinMode(18, INPUT);
  pinMode(17, OUTPUT);
  digitalWrite(signalPin, LOW);
  lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("SMART DOOR LOCK");
      lcd.setCursor(0,2); 
      lcd.print("Developed By:");
      lcd.setCursor(0,3); 
      lcd.print("!!!! SOUL IOT !!!!!");
      delay(3000);
lcd.clear();     
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

//  pinMode(ledPin, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void callback(char* Topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(Topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

if(strstr(Topic,sub2.c_str())){
  if (messageTemp == "correct") // equal to (strcmp(Data, Master) == 0)

    {

      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("User Stat:");
      lcd.setCursor(0,1); 
      lcd.print("  Valid User      ");
      Serial.println("Correct");
    digitalWrite(17, HIGH);
    delay(100);
    digitalWrite(17, LOW);
    delay(50);
    digitalWrite(17, HIGH);
    delay(250);
    digitalWrite(17, LOW);
    delay(50);
    digitalWrite(signalPin, HIGH);
      /*lcd.setCursor(0,2); 
      lcd.print("Door Stat:");
      lcd.setCursor(11,2); 
      lcd.print("Open");*/
      doorStat = "Open";
      lcd.setCursor(0,2); 
      lcd.print("Door Stat:");
      lcd.setCursor(0,3); 
      lcd.print(doorStat);
      client.publish(topic.c_str(),doorStat.c_str());
      //client.publish(topic3.c_str(),"Sucessful Entry");
      delay(3000);
      door = 0;
      count = 0;
      us = 0;
      clearData();

    }
    if (messageTemp == "incorrect"){

      Serial.println("Incorrect");
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Password Stat:");
      lcd.setCursor(0,1); 
      lcd.print(" !!!Incorrect!!!      ");
      doorStat = "Closed";
      client.publish(topic.c_str(),doorStat.c_str());
      //client.publish(topic2.c_str(),"Incorrect Password");
      digitalWrite(17, HIGH);
      delay(500);
      digitalWrite(17, LOW);
      delay(150);
      digitalWrite(17, HIGH);
      delay(750);
      digitalWrite(17, LOW);
      delay(2000);
      count ++;
      lcd.clear();
      clearData();
      door = 1;
      us = 0;

    }
}
if(strstr(Topic,sub.c_str()))
{
  if(messageTemp == "reset_1")
  {
    //lcd.clear();
     // lcd.setCursor(0,0); 
      Serial.println("Ask Admin to Restart the lock");
     // lcd.setCursor(0,1); 
     // lcd.print("Restart the lock ");
     
    //delay(3000);
    //ESP.restart();
    
  }
}
if(strstr(Topic,sub1.c_str()))
{
  if(messageTemp == "reset_0")
  {
   lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Door Lock Restarts");
      lcd.setCursor(0,1); 
      lcd.print("In 3 Seconds ..... ");
     
    delay(3000);
    ESP.restart(); 
  }
 
}
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(sub.c_str());
      //client.subscribe("smart_door_lock/XYZSchool/validation_pass_status");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop()

{
  delay(100);
  int x = digitalRead(35);
  int y = digitalRead(18);
  if (door == 0)

  {

    customKey = customKeypad.getKey();

    if (x == 0)

    {
      delay(1000);
      digitalWrite(signalPin, LOW);
      /*lcd.setCursor(0,2); 
      lcd.print("Door Stat:");
      lcd.setCursor(11,2); 
      lcd.print("Closed      ");*/
    doorStat = "Closed";
      lcd.clear();
      door = 1;
      us = 0;

    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Door Stat:  ");
      lcd.setCursor(0,1); 
      lcd.print(doorStat);
      lcd.setCursor(0,2); 
      lcd.print(" Close the door");
      lcd.setCursor(0,3); 
      lcd.print(" Thank You!!!");
      delay(1000);
      lcd.clear();
    }

  }
  //int x = digitalRead(35);
  
  if((door == 1) && (x ==0) && (us == 0))
  {
    user_valid();
  }
  if((door == 1) && (x ==0) && (us == 1))
  {
    pass_Open();
  }
  if ((door == 1) && (x ==1))
  {
    doorStat = "Forced Entry";
    lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Door Stat:  ");
      lcd.setCursor(0,1); 
      lcd.print("Forced Entry!!!  ");
      lcd.setCursor(0,2); 
      lcd.print("Contact Police      ");
    Serial.println(doorStat);
    digitalWrite(17, HIGH);
    delay(1000);
    digitalWrite(17, LOW);
    delay(100);
    digitalWrite(17, HIGH);
    delay(1500);
    digitalWrite(17, LOW);
    delay(3000);
    lcd.clear();
  }
  if(count > 3)
  {
    doorStat = "Invalid_User";
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Password Stat:");
      lcd.setCursor(0,1); 
      lcd.print("Multiple Wrong Entry      ");
      lcd.setCursor(0,2); 
      lcd.print("Contact Authority");
      lcd.setCursor(0,3); 
      lcd.print("For Access");
    Serial.println(doorStat);
    digitalWrite(17, HIGH);
    delay(1000);
    digitalWrite(17, LOW);
    delay(100);
    digitalWrite(17, HIGH);
    delay(1500);
    digitalWrite(17, LOW);
    delay(50);
  }
  if(y == 1)
  {
    digitalWrite(signalPin, HIGH);
    doorStat = "Opened";
      lcd.setCursor(0,2); 
      lcd.print("Door Stat:");
      lcd.setCursor(0,3); 
      lcd.print(doorStat);
      delay(3000);
      door = 0;
  }
   lcd.setCursor(0,2);
lcd.print("Door Stat:");
      lcd.setCursor(0,3); 
      lcd.print(doorStat);
}

void clearData()

{

  while (data_count != 0)

  { // This can be used for any array size,

    Data[data_count--] = 0; //clear array for new data

  }

  return;

}

void pass_Open()

{
  //lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print(" Enter Password");

  customKey = customKeypad.getKey();

  if ((customKey!='*') || (customKey!='#')) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)

  {

    Data1[data_count] = customKey; // store char into data array

    lcd.setCursor(data_count, 1); // move cursor to show each new char

    lcd.print("*"); // print char at said cursor

    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered

  }

  if (customKey == '#') // if the array index is equal to the number of expected chars, compare data to master

  {
    String t = String(Data)+"@"+String(Data1)+ "@" + school_id + "/";
    t = topic + "/" + t + "door";
    client.publish(topic.c_str(),t.c_str());
  }
  if (customKey=='*')
  {
    Data1[data_count--] = 0;
    lcd.setCursor(data_count, 1); // move cursor to show each new char

    lcd.print(" ");
  }

    

  }

void user_valid()

{

  lcd.setCursor(0, 0);

  lcd.print("Enter Emplyoee ID:");

  customKey = (char)customKeypad.getKey();

  if ((customKey!='*') || (customKey!='#')) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)

  {

    Data[data_count] = customKey; // store char into data array

    lcd.setCursor(data_count, 1); // move cursor to show each new char

    lcd.print(Data[data_count]); // print char at said cursor

    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered

  }

  if (customKey =='#') // if the array index is equal to the number of expected chars, compare data to master

  {
    //client.publish("smart_door_lock/XYZSchool/user_data",Data );
    us = 1;
  }
  if (customKey =='*')
  {
    Data[data_count--] = 0;
    lcd.setCursor(data_count, 1); // move cursor to show each new char

    lcd.print(" ");
  }

    

  }




