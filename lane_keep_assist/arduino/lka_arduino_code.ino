/*
 * Lane Keep Assist - Arduino side
 * Receives steering angle over Serial in the format "S<angle>\n",
 * where <angle> is in the range -90..+90 degrees.
 * The sketch maps this to a standard 0–180° servo signal.
 */

#include <Servo.h>

Servo steeringServo;
const uint8_t SERVO_PIN = 9;

void setup() {
  Serial.begin(9600);
  steeringServo.attach(SERVO_PIN);
  steeringServo.write(90);  // centre on start
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'S') {
      // Read the rest of line up to newline
      String angleStr = Serial.readStringUntil('\n');
      angleStr.trim();
      float angle = angleStr.toFloat();  // -90 .. +90
      angle = constrain(angle, -90, 90);
      int servoAngle = int(angle + 90);  // map to 0..180
      steeringServo.write(servoAngle);
    }
  }
}
