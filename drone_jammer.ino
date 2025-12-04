#include <ESP8266WiFi.h>

const char* ssid = "Dreams in Jail";
const char* password = "slytherdor";

IPAddress receiverIP(192, 168, 1, 100);  // receiver IP
const int port = 1234;

WiFiClient client;

void connectToWiFi() {
  WiFi.disconnect();
  delay(500);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  WiFi.channel(1);  //congesting Channel 1
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {
  if (client.connect(receiverIP, port)) {
    for (int i = 0; i < 100; i++) {
      client.print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
      delay(5); 
    }
    client.stop();
    Serial.println("Sent a burst of noise packets");
  } else {
    Serial.println("Failed to connect to receiver");
  }

  delay(500);
}
