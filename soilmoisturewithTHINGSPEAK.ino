#include <WiFi.h>

const char* ssid = "RedmiK50i";    // Enter your Wi-Fi network name (SSID)
const char* password = "whatever"; // Enter your Wi-Fi password
const char* server = "api.thingspeak.com";
const String apiKey = "W2KLXB3CHWAQ1MZA"; // Enter your ThingSpeak API key
const int analogInPin = A0;  // Analog input pin that the soil moisture sensor is connected to

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi network
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
}

void loop() {
  // Read soil moisture sensor data
  int sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);

  // Send data to ThingSpeak
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(server, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  String postStr = apiKey;
  postStr += "&field1=";
  postStr += String(sensorValue);
  postStr += "\r\n\r\n";

  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(postStr.length());
  client.print("\n\n");
  client.print(postStr);

  Serial.println("Data sent to ThingSpeak");
  delay(15000); // Wait 15 seconds before sending the next set of data
}

