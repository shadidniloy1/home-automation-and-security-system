#include <WiFi.h>

#define PIR_PIN 27
#define BUZZER_PIN 26
#define LED_PIN 25

const char* ssid = "VIVO Y02A";
const char* password = "aaaaaaaa";

bool armed = true;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to hotspot...");
}

void loop() {
  // Check WiFi status
  if (WiFi.status() == WL_CONNECTED) {
    armed = false;   // You are home
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    Serial.println("DISARMED (Hotspot detected)");
  } else {
    armed = true;    // You are away
    Serial.println("ARMED (No hotspot)");
  }

  // Motion detection
  if (armed && digitalRead(PIR_PIN) == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("🚨 UNAUTHORIZED MOTION!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);
}
