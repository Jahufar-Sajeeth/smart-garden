#include <WiFi.h>  // Include the Wi-Fi library for ESP32

// Replace these with your Wi-Fi network credentials
const char* ssid = "PRIYAN.V";
const char* password = "1234abcd";

void setup() {
  // Start the serial communication at a baud rate of 115200
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Once connected, print the IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Empty loop since we're just demonstrating how to get the IP address
}
