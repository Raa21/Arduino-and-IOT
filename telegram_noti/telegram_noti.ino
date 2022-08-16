#include "CTBot.h"
CTBot myBot;

String ssid  = "<YOUR_SSID>"; 
String pass  = "<YOUR_PASSWORD>"; 
String token = "<YOUR_TOKEN>";                        

void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOT OK");

}

void loop() {
     
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("Hello")) {                 // "Hello" messages received by bot
      // you can do some stuff here      
      myBot.sendMessage(msg.sender.id, "Nice to meet you!");  // Bot send a message to you
    }
    else if (msg.text.equalsIgnoreCase("Thank you")) {        
      // you can do some stuff here            
      myBot.sendMessage(msg.sender.id, "You're welcome!");    
    }
    else {                                                    // otherwise...
      // generate the message for the sender
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Try to send 'Hello' or 'Thank you'.";
      myBot.sendMessage(msg.sender.id, reply);                
    }
   
  }
  
  delay(500); // wait 500 milliseconds
