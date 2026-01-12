#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);
  bool ok = WiFi.softAP("TEST_AP", "12345678");

  Serial.println(ok ? "AP STARTED" : "AP FAILED");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {}
