#include <WiFi.h>
#include <WiFiClient.h>

const char* WIFI_SSID   = "Sajeeth";     // Wifi host name
const char* WIFI_PASS   = "12345678";       // Wifi password
const char* SERVER_IP   = "192.168.137.1";  // Server IP address established from pc
const int SERVER_PORT   = 12345;            // Port number for identify service

WiFiClient client;  // API connector for socket service

// Possible Replies from server
String turn_on  = "TURN_ON";
String turn_off = "TURN_OFF";
String module_name = "esp32warroom32";

// Possible Request to server
String login_request = "log_esp32warroom32@asdf@asdf123";

String output = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  while (!client.connected()) {
    client.connect(SERVER_IP, SERVER_PORT);
  }

  client.println(module_name);
  client.println(login_request);
}

void loop() {
  String uno_req = "";
  while (uno_req == "") {
    uno_req = Serial.readStringUntil('\n');
  }
  client.println(uno_req);
  Serial.println(uno_req);
  delay(100);
}
