/*
#include <PubSubClient.h>
const char* mqtt_server = "localhost"; // replace with the IP address of your Mosquitto broker if it is not running on the same machine
const int mqtt_port = 1883;
const char* mqtt_topic = "arduino/test"; // replace with the topic that you want to publish to or subscribe to
const char* mqtt_client_name = "tinkercad-arduino"; // replace with any unique identifier for your client


WiFiClient wifiClient;
PubSubClient mqttClient(mqtt_server, mqtt_port, wifiClient);
*/

int buttonState = 0;

void setup()
{
  
  /*
    mqttClient.setCallback(mqtt_callback);
    mqttClient.connect(mqtt_client_name);
    mqttClient.subscribe(mqtt_topic);
  */
  
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  mqttClient.publish(mqtt_topic, "Upaljen sam");
  
  buttonState = digitalRead(2);
  
  if(buttonState == HIGH){
      
    int brojac=10000;
    while(brojac!=0){
      
         digitalWrite(13, HIGH);
         digitalWrite(13, LOW);
         brojac--;
    }
  }
}