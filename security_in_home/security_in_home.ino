const int pirPin = 27;     
const int ledPin = 25;     
const int buttonPin = 14;  
bool armed = false;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
  delay(20000);
  
  Serial.println("Security System Ready - Button toggles ARM/DISARM");
  printStatus();
}

void loop() {
  // Check button first
  static bool lastButton = HIGH;
  bool button = digitalRead(buttonPin);
  if (button == LOW && lastButton == HIGH) {  // Button pressed (rising edge)
    armed = !armed;
    delay(50);  // Debounce
    printStatus();
  }
  lastButton = button;
  
  // Motion check ONLY when armed (silent when disarmed)
  static bool lastPir = LOW;
  bool pir = digitalRead(pirPin);
  
  if (armed) {
    if (pir == HIGH && lastPir == LOW) {
      digitalWrite(ledPin, HIGH);
      Serial.println("*** MOTION DETECTED - LED ON ***");
    } else if (pir == LOW && lastPir == HIGH) {
      digitalWrite(ledPin, LOW);
      Serial.println("Motion cleared - LED OFF");
    }
  }
  
  lastPir = pir;
  delay(100);
}

void printStatus() {
  Serial.printf("System %s\n", armed ? "ARMED" : "DISARMED");
  Serial.println("---");
}
