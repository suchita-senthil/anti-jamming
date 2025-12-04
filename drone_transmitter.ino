#include <ESP8266WiFi.h>

const char* ssid = "Dreams in Jail";
const char* password = "slytherdor";

IPAddress receiverIP(192, 168, 1, 100); 
const uint16_t port = 1234;

int currentChannel = 1;
WiFiClient client;

void connectToWiFi(int channel) {
  WiFi.disconnect();
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting on channel ");
  Serial.println(channel);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  WiFi.channel(channel);

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

bool sendMessageAndWaitForACK() {
  if (!client.connect(receiverIP, port)) {
    Serial.println("Connection to receiver failed");
    return false;
  }

  Serial.println("Connected to receiver, sending message...");
  client.println("S Hello");

  unsigned long startTime = millis();
  while (client.connected() && !client.available()) {
    if (millis() - startTime > 3000) { 
      Serial.println("ACK timeout");
      client.stop();
      return false;
    }
    delay(10);
  }

  if (client.available()) {
    String ack = client.readStringUntil('\n');
    ack.trim();
    if (ack == "ACK") {
      Serial.println("Received ACK from receiver");
      client.stop();
      return true;
    }
  }

  client.stop();
  return false;
}

void setup() {
  Serial.begin(9600);
  delay(10);
  connectToWiFi(currentChannel);
}

void loop() {
  Serial.print("Sending to receiver on channel ");
  Serial.println(currentChannel);

  bool success = sendMessageAndWaitForACK();
  if (!success) {
    // switching if no ACK 
    currentChannel = (currentChannel == 1) ? 2 : 1;
    Serial.println("Switching channel due to no ACK");
    connectToWiFi(currentChannel);
  }

  delay(5000);  
}
