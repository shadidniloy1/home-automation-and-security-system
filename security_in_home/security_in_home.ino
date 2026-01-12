#include <WiFi.h>

const char* hotspotSSID = "Niloy";  // ← CHANGE THIS
const char* hotspotPassword = "aaaaaaaa"; // ← CHANGE THIS

const int pirPin = 27;
const int ledPin = 25;
const int buzzerPin = 26;

bool wifiConnected = false;
unsigned long lastWifiCheck = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(pirPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  delay(20000);  // PIR warm-up
  
  Serial.println("WiFi Security System Ready");
  Serial.println("Connected to hotspot = ARMED (safe)");
  Serial.println("Disconnected = DISARMED (ALARM triggers)");
  printStatus();
  
  WiFi.begin(hotspotSSID, hotspotPassword);
  Serial.printf("Connecting to hotspot: %s\n", hotspotSSID);
}

void loop() {
  // Check WiFi status every 5 seconds
  if (millis() - lastWifiCheck > 5000) {
    wifiConnected = (WiFi.status() == WL_CONNECTED);
    if (wifiConnected != lastWifiCheck / 5000) {  // Status changed
      printStatus();
    }
    lastWifiCheck = millis();
  }
  
  // ALARM only when WiFi DISCONNECTED (DISARMED)
  if (!wifiConnected && digitalRead(pirPin) == HIGH) {
    // TRIGGER ALARM
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("*** INTRUDER ALERT! WiFi OFF - MOTION DETECTED ***");
    delay(1000);  // Alarm for 1s, repeat
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}

void printStatus() {
  if (wifiConnected) {
    Serial.println("ARMED: Connected to hotspot ✓ (Motion ignored)");
  } else {
    Serial.println("DISARMED: No WiFi connection ✗ (ALARM ACTIVE)");
  }
  Serial.println("---");
}
