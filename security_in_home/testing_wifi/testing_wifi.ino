#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);
  bool ok = WiFi.softAP("ESP32_TEST", "12345678");

  Serial.println(ok ? "AP STARTED" : "AP FAILED");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {}
