#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid = "ssid";
const char* password =  "paswd";
const char* mqtt_server = "127.0.0.1";//ip of message broker

const char* message_on = "ON";
const char* message_off = "OFF";

#define led  16

WiFiClient WiFiclient;
PubSubClient client(WiFiclient);
 
unsigned long lastMillis = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  const int kLenght = length;
  char message[kLenght];
  for(int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
  Serial.print("Message : ");
  Serial.println(message);
  //we have relay of disconnection
  if (!strcmp(message, message_on)) {
      digitalWrite(led, LOW);
  }
  if (!strcmp(message, message_off)) {
    digitalWrite(led, HIGH);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      // Serial Pring just for DEBUGING
      Serial.println("connected");
      // Once connected, publish an announcement...
      // ... and resubscribe
      client.subscribe("esp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
 Serial.begin(115200);
 delay(10);
 Serial.println();
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
 delay(2000);
  pinMode(led, OUTPUT);

 Serial.print("connecting to MQTT broker...");
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
}
 


void loop() {
 if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
 
