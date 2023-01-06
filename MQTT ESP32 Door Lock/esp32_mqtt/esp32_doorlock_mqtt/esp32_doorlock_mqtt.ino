#include <WiFi.h>
#include <PubSubClient.h>
#include <Keypad.h>
#define Password_Length 8

// Replace the next variables with your SSID/Password combination
const char* ssid = "SVTRAPTOR";
const char* password = "1234567809";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int signalPin = 12;
int flag =0;
String passString = "";
String doorString = "Closed";

char Data[Password_Length]; 
char Master[Password_Length] = "123A456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// LED Pin
const int ledPin = 4;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(signalPin, OUTPUT);
  pinMode(11, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(signalPin, HIGH);
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

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  /*if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }*/
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      //client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 20 seconds before retrying
      delay(5000);
    }
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();

  int x = digitalRead(11);
  Serial.println("Enter Password:");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey;  
    data_count++; 
    }

  if(data_count == Password_Length-1){

    if(!strcmp(Data, Master)){
      Serial.println("Correct");
      passString = "Correct" ;
      client.publish("esp32/Pin_Status", passString.c_str());
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(10, LOW);
    delay(50);
    digitalWrite(10, HIGH);
    delay(250);
    digitalWrite(10, LOW);
    delay(50);
      if ((x == 0) && (flag ==0)){
      digitalWrite(signalPin, LOW);
      doorString = "Open";
      client.publish("esp32/Door_Status", doorString.c_str()); 
      flag =1;
    delay(10000); 
    
      //digitalWrite(signalPin, HIGH);
      }
      
    }
    else{
      Serial.println("Incorrect");
      passString = "Incorrect";
      client.publish("esp32/Pin_Status", passString.c_str());
      digitalWrite(10, HIGH);
      delay(500);
      digitalWrite(10, LOW);
      delay(150);
      digitalWrite(10, HIGH);
      delay(750);
      digitalWrite(10, LOW);
      delay(150);
      }
    clearData();  
  }
  if ((x == 0) && (flag ==1)){
    digitalWrite(signalPin, HIGH);
    doorString = "Closed";
    client.publish("esp32/Door_Status", doorString.c_str());
    delay(1000);
    //flag = 0;
  }
  if ((x == 1) && (flag ==0)){
    doorString = "Forced_Entry";
    client.publish("esp32/Door_Status", doorString.c_str());
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);
    delay(100);
    digitalWrite(10, HIGH);
    delay(1500);
    digitalWrite(10, LOW);
    delay(50);
  }
  //doorString = "Closed";
  client.publish("esp32/Door_Status", doorString.c_str());  
  delay(10);
}
