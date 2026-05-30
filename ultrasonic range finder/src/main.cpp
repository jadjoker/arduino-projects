#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin   = 12;
const int echoPin   = 13;
const int redPin    = 9;
const int greenPin  = 10;
const int bluePin   = 11;
const int laserPin  = 7;
const int buttonPin = 2;

bool laserOn = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(trigPin,   OUTPUT);
  pinMode(echoPin,   INPUT);
  pinMode(redPin,    OUTPUT);
  pinMode(greenPin,  OUTPUT);
  pinMode(bluePin,   OUTPUT);
  pinMode(laserPin,  OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance meter");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();

  Serial.begin(9600);
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

void setColor(int r, int g, int b) {
  analogWrite(redPin,   r);
  analogWrite(greenPin, g);
  analogWrite(bluePin,  b);
}

void loop() {
  // ---- Button: toggle laser on falling edge only ----
  bool currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    laserOn = !laserOn;
    digitalWrite(laserPin, laserOn ? HIGH : LOW);
    lcd.setCursor(8, 1);
    lcd.print(laserOn ? "LZR:ON  " : "LZR:OFF ");
  }
  lastButtonState = currentButtonState;

  // ---- Measure ----
  long dist = getDistanceCm();

  // ---- LCD ----
  lcd.setCursor(0, 0);
  if (dist < 0) {
    lcd.print("Out of range    ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  } else {
    lcd.print("Dist: ");
    lcd.print(dist);
    lcd.print(" cm     ");
    lcd.setCursor(0, 1);
    if      (dist > 40) lcd.print("Zone: FAR       ");
    else if (dist > 15) lcd.print("Zone: MEDIUM    ");
    else                lcd.print("Zone: CLOSE     ");
  }

  // ---- RGB LED ----
  if      (dist < 0)   setColor(0, 0, 255);
  else if (dist > 40)  setColor(0, 255, 0);
  else if (dist > 15)  setColor(255, 165, 0);
  else                 setColor(255, 0, 0);

  delay(100);
}
