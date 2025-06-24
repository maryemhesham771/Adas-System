const int MOTOR_PIN = 9;
const int BUZZER_PIN = 10;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "go") {
      digitalWrite(MOTOR_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
    } else if (command == "stop") {
      digitalWrite(MOTOR_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
    }
  }
}
