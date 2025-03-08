// Define the pin numbers
const int pirPin = 13;   // PIR sensor input pin
const int buzzer = 7;    // Buzzer output pin
const int relayPin = 3;  // Relay output pin
const int waterLevelPin = A0; // Water level sensor pin

int pirVal = 0;

// Threshold for water level (this value may need calibration based on your sensor)
const int waterLevelThreshold = 500;

String output_state = "on";
String esp32_reply = "";

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  if (output_state == "on") {
    String msg = "send_to_mobile@";
    pirVal = digitalRead(pirPin);
    int waterLevel = analogRead(waterLevelPin);
    
    bool isWaterLevelLow  = false;
    bool isMotionDetected = false;
    bool isBuzzerActionNeed = false;
    bool isRelayActionNeed = false;

    if (waterLevel < waterLevelThreshold) {
      isWaterLevelLow = true;
    }

    if (pirVal == HIGH) {
      isMotionDetected = true;
    }

    if (!isWaterLevelLow && !isMotionDetected) {
      msg = msg + "WATER_LVL:HIGH#MOTION_SENCE:LOW";
      Serial.println(msg);
    } else 
    if (!isWaterLevelLow && isMotionDetected) {
      msg = msg + "WATER_LVL:HIGH#MOTION_SENCE:HIGH";
      isBuzzerActionNeed = true;
      isRelayActionNeed = true;
      Serial.println(msg);
    } else 
    if (isWaterLevelLow && !isMotionDetected) {
      msg = msg + "WATER_LVL:LOW#MOTION_SENCE:LOW";
      isBuzzerActionNeed = true;
      Serial.println(msg);
    } else 
    if (isWaterLevelLow && isMotionDetected) {
      msg = msg + "WATER_LVL:LOW#MOTION_SENCE:HIGH";
      isBuzzerActionNeed = true;
      Serial.println(msg);
    } 
    if (isBuzzerActionNeed) {
      tone(buzzer, 500);
      if (isRelayActionNeed) {
        digitalWrite(relayPin, HIGH);
      }
      delay(5000);
      noTone(buzzer);
      digitalWrite(relayPin, LOW);
    } else {
      delay(1000);
    }
  }
}
