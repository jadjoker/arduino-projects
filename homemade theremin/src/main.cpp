#include <Arduino.h>

const int trigPin   = 12;
const int echoPin   = 13;
const int buzzerPin = 8;
const int buttonPin = 2;
const int statusLed = 9;

bool thereminOn = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(trigPin,   OUTPUT);
  pinMode(echoPin,   INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(statusLed, OUTPUT);

  digitalWrite(statusLed, LOW);
  noTone(buzzerPin);

  Serial.begin(9600);
  Serial.println("Homemade Theremin ready");
}

long getDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    return -1;
  }
  return round(duration * 0.0343 / 2);
}

const char* noteLabel(int frequency) {
  if (frequency < 262) return "C4";
  if (frequency < 294) return "D4";
  if (frequency < 330) return "E4";
  if (frequency < 350) return "F4";
  if (frequency < 394) return "G4";
  if (frequency < 442) return "A4";
  return "B4";
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    thereminOn = !thereminOn;
    digitalWrite(statusLed, thereminOn ? HIGH : LOW);
    if (!thereminOn) {
      noTone(buzzerPin);
    }
  }
  lastButtonState = currentButtonState;

  long distance = getDistanceCm();

  if (thereminOn && distance > 0) {
    int frequency = map(constrain(distance, 5, 60), 60, 5, 220, 880);
    tone(buzzerPin, frequency);
    Serial.print("Distance: "); Serial.print(distance);
    Serial.print(" cm, Tone: "); Serial.print(frequency);
    Serial.print(" Hz ("); Serial.print(noteLabel(frequency)); Serial.println(")");
  } else {
    noTone(buzzerPin);
    if (thereminOn) {
      Serial.println("Move your hand over the sensor to play notes.");
    } else {
      Serial.println("Theremin is off. Press the button to enable sound.");
    }
  }

  delay(150);
}
