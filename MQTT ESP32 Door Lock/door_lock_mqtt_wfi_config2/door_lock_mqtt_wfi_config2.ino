#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <WiFiManager.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  

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

int signalPin = 23;

#define P_Lenght 15 // Give enough room for six chars + NULL char
#define U_Lenght 8

char Data1[P_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Data[U_Lenght];
//char Master1[P_Lenght] = "123A";
//char Master[U_Lenght] = "0005";
String val_stat = "";
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

int door = 1;
int count = 0;
String doorStat = "Closed";
byte rowPins[ROWS] = {32, 33, 27, 14}; //connect to the row pinouts of the keypad

byte colPins[COLS] = {16, 4, 2, 15}; //connect to the column pinouts of the keypad

const int ledPin = 2;
String ledState;

Keypad customKeypad = Keypad( makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

void setup()

{

  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  lcd.begin();                     
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
  pinMode(35, INPUT);
  pinMode(34, INPUT);
  pinMode(18, INPUT);
  pinMode(17, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(signalPin, LOW);
  Serial.println(topic);
  lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("SMART DOOR LOCK");
      lcd.setCursor(0,2); 
      lcd.print("Developed By:");
      lcd.setCursor(0,3); 
      lcd.print("!!!! SOUL IOT !!!!!");
      delay(3000);
  lcd.clear();
  Serial.println("Setting AP (Access Point)");
    WiFi.mode(WIFI_STA);
     // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    //wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("Door Lock","Soul@1234"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        
      delay(3000);
    }
     
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
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
  lcd.setCursor(0,0); 
      lcd.print("Message Type:");
      lcd.setCursor(0,1); 
      lcd.print(messageTemp);
      lcd.setCursor(0,2); 
      lcd.print("Topic:");
      lcd.setCursor(0,3); 
      lcd.print(Topic);
      delay(2000);

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
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
     // delay(5000);
    }
  }
}
void loop()

{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  int x = digitalRead(35);
  int y = digitalRead(18);
 if (door == 0)

  {

    //customKey = customKeypad.getKey();

    if (x == 0)

    {
      delay(1000);
      digitalWrite(signalPin, LOW);
      /*lcd.setCursor(0,2); 
      lcd.print("Door Stat:");
      lcd.setCursor(11,2); 
      lcd.print("Closed      ");*/
    doorStat = "Closed";
//    String topic = 
    client.publish(topic.c_str(),doorStat.c_str());
      lcd.clear();
      door = 1;

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
      client.publish(topic.c_str(),doorStat.c_str());
      delay(1000);
      lcd.clear();
    }

  }
  //int x = digitalRead(35);
  
  if((door == 1) && (x ==0))
  {
    user_valid();
  }
  if ((door == 1) && (x ==1))
  {
    doorStat = "Open";
    lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Door Stat:  ");
      lcd.setCursor(0,1); 
      lcd.print(doorStat);
      lcd.setCursor(0,2); 
      lcd.print("   Forced Entry!!!  ");
      lcd.setCursor(0,3); 
      lcd.print("   Contact Police      ");
      client.publish(topic.c_str(),doorStat.c_str());
     // client.publish(topic2.c_str(),"Forced Entry");
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
  if(count > 5)
  { 
    doorStat = "Closed";
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Password Stat:");
      lcd.setCursor(0,1); 
      lcd.print("Multiple Wrong Entry      ");
      lcd.setCursor(0,2); 
      lcd.print("Contact Authority");
      lcd.setCursor(0,3); 
      lcd.print("For Access");
      String a = topic + "/" + "1@" + device_id + "@" + school_id + "/" + "ping";
      String b = doorStat + "/Multiple_Wrong_Entry";
      //client.publish(topic.c_str(),doorStat.c_str());
      //client.publish(topic.c_str(),"Invalid_User");
      client.publish(topic.c_str(),a.c_str());
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
    lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print(" Stat:");
      lcd.setCursor(0,1); 
      lcd.print("  Valid User      ");
      Serial.println("Correct");
      digitalWrite(signalPin, HIGH);
      doorStat = "Open";
      lcd.setCursor(0,2); 
      lcd.print("Door Stat:");
      lcd.setCursor(0,3); 
      lcd.print(doorStat);
      client.publish(topic.c_str(),doorStat.c_str());
      //client.publish(topic3.c_str(),"Exit");
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
    Data1[data_count--] = 0;
  }

  return;

}

void pass_Open()

{

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

    //lcd.clear();

  }

void user_valid()

{

  lcd.setCursor(0, 0);

  lcd.print(" Enter User");

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
    pass_Open();
  }
  if (customKey =='*')
  {
    Data[data_count--] = 0;
    lcd.setCursor(data_count, 1); // move cursor to show each new char

    lcd.print(" ");
  }

   // lcd.clear();

  }

