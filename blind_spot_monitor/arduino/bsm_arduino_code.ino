/*
 * Blind‑Spot Monitor – Arduino side
 * Expects lines of the form "L<0|1>R<0|1>\n"
 * where L and R indicate whether an object is present
 * in the left or right blind spot. The sketch lights
 * indicator LEDs and actuates a buzzer accordingly.
 */

const uint8_t LEFT_LED  = 8;
const uint8_t RIGHT_LED = 9;
const uint8_t BUZZER    = 10;

void setup() {
  pinMode(LEFT_LED,  OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(BUZZER,    OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    int lIdx = line.indexOf('L');
    int rIdx = line.indexOf('R');

    if (lIdx >= 0 && lIdx + 1 < line.length()) {
      bool leftAlert = line.charAt(lIdx + 1) == '1';
      digitalWrite(LEFT_LED, leftAlert);
    }
    if (rIdx >= 0 && rIdx + 1 < line.length()) {
      bool rightAlert = line.charAt(rIdx + 1) == '1';
      digitalWrite(RIGHT_LED, rightAlert);
    }

    // Buzzer if either side alerts
    bool alert = digitalRead(LEFT_LED) || digitalRead(RIGHT_LED);
    digitalWrite(BUZZER, alert);
  }
}
