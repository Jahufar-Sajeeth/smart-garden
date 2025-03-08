// Define the pin numbers
const int pirPin = 13;   // PIR sensor input pin
const int buzzer = 6;    // Buzzer output pin
const int relayPin = 3;  // Relay output pin
const int waterLevelPin = A0; // Water level sensor pin

// Variables to hold the current and previous PIR sensor states
int pirState = LOW;
int pirVal = 0;

// Threshold for water level (this value may need calibration based on your sensor)
const int waterLevelThreshold = 500;

void setup() {
  // Initialize the PIR sensor pin as an input
  pinMode(pirPin, INPUT);
  
  // Initialize the Buzzer and Relay pins as outputs
  pinMode(buzzer, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  // Start the Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the PIR sensor value
  pirVal = digitalRead(pirPin);
  
  // Read the water level sensor value
  int waterLevel = analogRead(waterLevelPin);
  
  // Check if the water level is below the threshold
  if (waterLevel < waterLevelThreshold) {
    // Print message to the Serial Monitor
    Serial.println("Low water level detected");
    
    // Turn on the Buzzer to indicate low water level
    digitalWrite(buzzer, HIGH);
    delay(2000); // Buzzer on for 2 seconds
    digitalWrite(buzzer, LOW);
  } else if (pirVal == HIGH) {
    // Check if the PIR state has changed
    if (pirState == LOW) {
      // Turn on the Buzzer and Relay
      digitalWrite(buzzer, HIGH);
      digitalWrite(relayPin, HIGH);
      
      // Print message to the Serial Monitor
      Serial.println("Motion detected");
      
      // Wait for 5 seconds
      delay(5000);
      
      // Turn off the Buzzer and Relay
      digitalWrite(buzzer, LOW);
      digitalWrite(relayPin, LOW);
      
      // Update the PIR state to HIGH to prevent immediate re-triggering
      pirState = HIGH;
    }
  } else {
    // Update the PIR state to LOW if no motion is detected
    pirState = LOW;
  }
}
