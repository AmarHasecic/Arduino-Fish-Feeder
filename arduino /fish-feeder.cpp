
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFiClientSecure.h>
#include<Servo.h>

Servo motor;

const char* ssid = "";
const char* password = "";


// MQTT broker credentials
#define MQTT_SERVER ""
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""

// MQTT client object and topics
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);
//Adafruit_MQTT_Publish mqttPublisher = Adafruit_MQTT_Publish(&mqtt, "amar_hasecic/feeds/buttonNahrani");
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, "amar_hasecic/feeds/buttonNahrani");


int pos;
void setup() {
 
  Serial.begin(9600);
  delay(11);
  Serial.println("Starting setup procedure...");

    WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  if(WiFi.status() == WL_CONNECTED)
  Serial.println("Connected to the network!");

  // Connect to Adafruit IO MQTT server
  mqttConnect();

  if(mqtt.subscribe(&onoffbutton) == true)
  Serial.println("Ready to receive messages");

  motor.attach(2, 500, 2500);
}

int connectionsCounter=0;
  
void loop() {

  if(connectionsCounter == 2147483647) connectionsCounter = 0;

  if(connectionsCounter==0)
     mqtt.disconnect();
     
  mqttConnect();
  connectionsCounter++;

 
    Adafruit_MQTT_Subscribe *subscription;
    while((subscription = mqtt.readSubscription(1000))) {
         if(subscription == &onoffbutton){

          Serial.println("Feeding time :)");
           
          for(int i=0; i<180; i++){
              motor.write(i); 
              delay(10); 
          }

          delay(5000);
          motor.write(0);
             
         }
      
    }
    

  delay(4000);
  if(! mqtt.ping()){
    mqtt.disconnect();
  }
}



void mqttConnect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}