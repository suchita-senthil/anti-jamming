#include <ESP8266WiFi.h>

const char* ap_ssid = "ESP_AP";
const char* ap_password = "espsoftap";
WiFiServer server(1234);
int currentChannel = 1;

void startSoftAP(int channel) {
  WiFi.softAPdisconnect(true); 
  delay(1000);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password, channel);
  server.begin();
  Serial.print("Receiver started on channel ");
  Serial.print(channel);
  Serial.print(" | IP: ");
  Serial.println(WiFi.softAPIP());
}

void setup() {
  Serial.begin(9600);
  startSoftAP(currentChannel);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");
    String msg = client.readStringUntil('\n');
    msg.trim();
    Serial.print("Received: ");
    Serial.println(msg);
    
    if (msg.startsWith("S")) {
      client.println("ACK");
      Serial.println("Sent ACK");
    } else {
      Serial.println("Jammed message detected, switching channel...");
      currentChannel = (currentChannel == 1) ? 6 : 1;
      startSoftAP(currentChannel); 
    }

    client.stop();
  }
}
