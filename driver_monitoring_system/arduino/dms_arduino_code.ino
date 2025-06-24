/*
 * Driver Monitoring System – Arduino side
 * Receives keyword commands terminated by newline:
 *   BUZZER_ON   / BUZZER_OFF
 *   WARNING     / NORMAL
 *   STOP
 * Use digital outputs for buzzer, vibration motor, and braking relay.
 */

const uint8_t BUZZER_PIN   = 8;
const uint8_t VIBRO_PIN    = 9;
const uint8_t BRAKE_RELAY  = 10;

void setup() {
  pinMode(BUZZER_PIN,  OUTPUT);
  pinMode(VIBRO_PIN,   OUTPUT);
  pinMode(BRAKE_RELAY, OUTPUT);

  digitalWrite(BUZZER_PIN,  LOW);
  digitalWrite(VIBRO_PIN,   LOW);
  digitalWrite(BRAKE_RELAY, LOW);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "BUZZER_ON") {
      digitalWrite(BUZZER_PIN, HIGH);
    }
    else if (cmd == "BUZZER_OFF") {
      digitalWrite(BUZZER_PIN, LOW);
    }
    else if (cmd == "WARNING") {
      digitalWrite(VIBRO_PIN, HIGH);
    }
    else if (cmd == "NORMAL") {
      digitalWrite(VIBRO_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }
    else if (cmd == "STOP") {
      digitalWrite(BRAKE_RELAY, HIGH); // Engage brake
      delay(2000);                     // Hold for 2 s
      digitalWrite(BRAKE_RELAY, LOW);
    }
  }
}
