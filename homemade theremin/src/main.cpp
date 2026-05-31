#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin   = 12;
const int echoPin   = 13;
const int buzzerPin = 8;
const int buttonPin = 2;
const int statusLed = 9;

bool thereminOn = false;
bool lastButtonState = HIGH;

// C major scale: C3 through B6 (4 octaves, 28 notes, ~3.4cm per note across 5-100cm)
const int notes[] = {
  131, 147, 165, 175, 196, 220, 247,   // C3 D3 E3 F3 G3 A3 B3
  262, 294, 330, 349, 392, 440, 494,   // C4 D4 E4 F4 G4 A4 B4
  523, 587, 659, 698, 784, 880, 988,   // C5 D5 E5 F5 G5 A5 B5
  1047,1175,1319,1397,1568,1760,1976   // C6 D6 E6 F6 G6 A6 B6
};
const char* noteNames[] = {
  "C3","D3","E3","F3","G3","A3","B3",
  "C4","D4","E4","F4","G4","A4","B4",
  "C5","D5","E5","F5","G5","A5","B5",
  "C6","D6","E6","F6","G6","A6","B6"
};
const int noteCount = 28;

void setup() {
  pinMode(trigPin,   OUTPUT);
  pinMode(echoPin,   INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(statusLed, OUTPUT);

  digitalWrite(statusLed, LOW);
  noTone(buzzerPin);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Theremin Ready");
  lcd.setCursor(0, 1);
  lcd.print("Press btn to play");

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
  if (duration == 0) return -1;
  return round(duration * 0.0343 / 2);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    thereminOn = !thereminOn;
    digitalWrite(statusLed, thereminOn ? HIGH : LOW);
    if (!thereminOn) noTone(buzzerPin);
  }
  lastButtonState = currentButtonState;

  long distance = getDistanceCm();

  if (thereminOn && distance > 0) {
    int idx = map(constrain(distance, 5, 100), 100, 5, 0, noteCount - 1);
    int frequency = notes[idx];
    tone(buzzerPin, frequency);

    lcd.setCursor(0, 0);
    lcd.print("Note: ");
    lcd.print(noteNames[idx]);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print(frequency);
    lcd.print(" Hz        ");

    Serial.print("Distance: "); Serial.print(distance);
    Serial.print(" cm  ->  "); Serial.print(noteNames[idx]);
    Serial.print(" ("); Serial.print(frequency); Serial.println(" Hz)");
  } else {
    noTone(buzzerPin);
    lcd.setCursor(0, 0);
    if (thereminOn) {
      lcd.print("Move hand...    ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      Serial.println("Move your hand over the sensor to play notes.");
    } else {
      lcd.print("Theremin  OFF   ");
      lcd.setCursor(0, 1);
      lcd.print("Btn to start    ");
      Serial.println("Theremin is off. Press the button to enable sound.");
    }
  }

  delay(150);
}
