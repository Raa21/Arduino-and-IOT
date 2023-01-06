#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);  
AsyncWebServer server(80);

const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";

String ssid;
String pass;

const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";

unsigned long previousMillis = 0;
const long interval = 10000;

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

void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}

// Initialize WiFi
bool initWiFi() {
  if(ssid=="" ){                                              
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      lcd.clear();
      Serial.println("Failed to connect.");
      lcd.setCursor(0,0); 
      lcd.print("Failed to connect.");
      delay(3000);
      lcd.clear();
      return false;
    }
  }
  lcd.clear();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,0); 
      lcd.print("WiFi connected");
      lcd.setCursor(0,1); 
      lcd.print("IP address:");
      lcd.setCursor(0,2); 
      lcd.print(WiFi.localIP());
      delay(2000);
      lcd.clear();
  return true;
}
String processor(const String& var) {
  if(var == "STATE") {
    if(digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return ledState;
  }
  return String();
}

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
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
}
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network

  initSPIFFS();
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  Serial.println(ssid);
  Serial.println(pass);
  if(initWiFi()) {
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });
    server.serveStatic("/", SPIFFS, "/");
    
    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(ledPin, HIGH);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(ledPin, LOW);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });
    server.begin();
  }
  else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 
    lcd.setCursor(0,0); 
      lcd.print("Setting Access Point");
      lcd.setCursor(0,1); 
      lcd.print("IP address:");
      lcd.setCursor(0,2); 
      lcd.print(IP);
      delay(5000);
      lcd.clear();

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/wifimanager.html", "text/html");
    });

    server.serveStatic("/", SPIFFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router");
      delay(3000);
      ESP.restart();
    });
    server.begin();
  }
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

      /*if(strstr(Topic,"smart_door_lock/validation_user_status")){
      if (messageTemp == "User_Valid") // equal to (strcmp(Data, Master) == 0)

    {

      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("User Stat:");
      lcd.setCursor(0,1); 
      lcd.print("    Correct      ");
      delay(2000);
      lcd.clear();
      Serial.println("Correct");
      clearData();
      pass_Open();

    }
    else{

      Serial.println("Incorrect");
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("User Stat:");
      lcd.setCursor(0,1); 
      lcd.print(" !!!Incorrect!!!      ");
      delay(2000);
      lcd.clear();
      clearData();

    }
      lcd.clear();
  Serial.println();
}*/
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
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
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

