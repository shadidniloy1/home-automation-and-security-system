#define SENSOR_PIN 27  // PIR sensor OUT connected here
#define LED_PIN 2     // Internal LED

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("--- Simple Motion Test Starting ---");
}

void loop() {
  int val = digitalRead(SENSOR_PIN); // Read the pin state (0 or 1)
  
  if (val == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("1 - MOTION!");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("0 - scanning...");
  }
  
  delay(100); // Fast refresh (10 times per second)
}