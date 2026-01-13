#include <Servo.h>

#define TRIG_PIN 11   
#define ECHO_PIN 10   
#define SERVO_PIN 3   

Servo doorServo; 
int currentAngle = 0; 

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    doorServo.attach(SERVO_PIN);
    doorServo.write(currentAngle); 
    Serial.begin(9600);
}

long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH);
    long distance = duration * 0.034 / 2; // Convert time to distance (cm)
    return distance;
}

void smoothServoMove(int targetAngle) {
    if (targetAngle > currentAngle) {  
        for (int angle = currentAngle; angle <= targetAngle; angle++) {
            doorServo.write(angle);
            delay(10); 
        }
    } else { 
        for (int angle = currentAngle; angle >= targetAngle; angle--) {
            doorServo.write(angle);
            delay(10); 
        }
    }
    currentAngle = targetAngle; 
}

void loop() {
    long distance = getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    if (distance > 0 && distance <= 3) { // If object detected within 3 cm
        smoothServoMove(90);
        delay(3000);
    } else {
        smoothServoMove(0);
    }
    delay(500);
}