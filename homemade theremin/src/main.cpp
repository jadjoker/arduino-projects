#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>
#include <Keypad.h>

// Pins
const int trigPin   = 12;
const int echoPin   = 13;
const int buzzerPin = 8;
const int buttonPin = 2;
const int statusLed = 9;
const int stripPin  = 6;

#define NUM_LEDS 8

CRGB leds[NUM_LEDS];
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad — rows: D3 D4 D5 D7 | cols: D10 D11 A0 A1
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3, 4, 5, 7};
byte colPins[COLS] = {10, 11, A0, A1};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- Scale definitions ---

// C Major: C D E F G A B  (28 notes, C3-B6)
const int notesMajor[]   = {131,147,165,175,196,220,247,262,294,330,349,392,440,494,523,587,659,698,784,880,988,1047,1175,1319,1397,1568,1760,1976};
const char* namesMajor[] = {"C3","D3","E3","F3","G3","A3","B3","C4","D4","E4","F4","G4","A4","B4","C5","D5","E5","F5","G5","A5","B5","C6","D6","E6","F6","G6","A6","B6"};

// Pentatonic: C D E G A  (20 notes, C3-A6)
const int notesPenta[]   = {131,147,165,196,220,262,294,330,392,440,523,587,659,784,880,1047,1175,1319,1568,1760};
const char* namesPenta[] = {"C3","D3","E3","G3","A3","C4","D4","E4","G4","A4","C5","D5","E5","G5","A5","C6","D6","E6","G6","A6"};

// Blues: C Eb F F# G Bb  (24 notes, C3-Bb6)
const int notesBlues[]   = {131,156,175,185,196,233,262,311,349,370,392,466,523,622,698,740,784,932,1047,1245,1397,1480,1568,1865};
const char* namesBlues[] = {"C3","Eb3","F3","F#3","G3","Bb3","C4","Eb4","F4","F#4","G4","Bb4","C5","Eb5","F5","F#5","G5","Bb5","C6","Eb6","F6","F#6","G6","Bb6"};

// Natural Minor: C D Eb F G Ab Bb  (28 notes, C3-Bb6)
const int notesMinor[]   = {131,147,156,175,196,208,233,262,294,311,349,392,415,466,523,587,622,698,784,831,932,1047,1175,1245,1397,1568,1661,1865};
const char* namesMinor[] = {"C3","D3","Eb3","F3","G3","Ab3","Bb3","C4","D4","Eb4","F4","G4","Ab4","Bb4","C5","D5","Eb5","F5","G5","Ab5","Bb5","C6","D6","Eb6","F6","G6","Ab6","Bb6"};

// Chromatic: all semitones  (36 notes, C4-B6, 3 octaves)
const int notesChrom[]   = {262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976};
const char* namesChrom[] = {"C4","C#4","D4","D#4","E4","F4","F#4","G4","G#4","A4","A#4","B4","C5","C#5","D5","D#5","E5","F5","F#5","G5","G#5","A5","A#5","B5","C6","C#6","D6","D#6","E6","F6","F#6","G6","G#6","A6","A#6","B6"};

struct Scale {
  const char*   name;
  const int*    notes;
  const char**  names;
  int           count;
};

const Scale scales[] = {
  {"C Major",   notesMajor, namesMajor, 28},
  {"Pentatonic",notesPenta, namesPenta, 20},
  {"Blues",     notesBlues, namesBlues, 24},
  {"Nat Minor", notesMinor, namesMinor, 28},
  {"Chromatic", notesChrom, namesChrom, 36},
};
const int scaleCount = 5;
int currentScale = 0;

bool thereminOn       = false;
bool lastButtonState  = HIGH;
unsigned long scaleChangedAt = 0;

// --- Helpers ---

void updateStrip(int idx, int total) {
  int lit = map(idx, 0, total - 1, 1, NUM_LEDS);
  uint8_t hue = map(idx, 0, total - 1, 0, 160); // red (low) → blue (high)
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = (i < lit) ? CHSV(hue, 255, 200) : CRGB::Black;
  }
  FastLED.show();
}

void clearStrip() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

long getDistanceCm() {
  digitalWrite(trigPin, LOW);  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;
  return round(duration * 0.0343 / 2);
}

// --- Setup ---

void setup() {
  pinMode(trigPin,   OUTPUT);
  pinMode(echoPin,   INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, LOW);
  noTone(buzzerPin);

  FastLED.addLeds<WS2812B, stripPin, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(150);
  clearStrip();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Theremin Ready  ");
  lcd.setCursor(0, 1); lcd.print("1-5: pick scale ");

  Serial.begin(9600);
  Serial.println("Theremin ready. Keys 1-5 select scale.");
}

// --- Loop ---

void loop() {
  // Button toggle
  bool currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    thereminOn = !thereminOn;
    digitalWrite(statusLed, thereminOn ? HIGH : LOW);
    if (!thereminOn) { noTone(buzzerPin); clearStrip(); }
  }
  lastButtonState = currentButtonState;

  // Keypad scale select (keys 1-5)
  char key = keypad.getKey();
  if (key >= '1' && key <= '5') {
    currentScale = key - '1';
    scaleChangedAt = millis();
    Serial.print("Scale: "); Serial.println(scales[currentScale].name);
  }

  // Show scale-changed banner for 1.5 s
  if (millis() - scaleChangedAt < 1500) {
    lcd.setCursor(0, 0); lcd.print("Scale:          ");
    lcd.setCursor(0, 1);
    lcd.print(scales[currentScale].name);
    lcd.print("            ");
    delay(150);
    return;
  }

  long distance = getDistanceCm();
  const Scale& s = scales[currentScale];

  if (thereminOn && distance > 0) {
    int idx = map(constrain(distance, 5, 100), 100, 5, 0, s.count - 1);
    tone(buzzerPin, s.notes[idx]);
    updateStrip(idx, s.count);

    lcd.setCursor(0, 0);
    lcd.print("Note: "); lcd.print(s.names[idx]); lcd.print("     ");
    lcd.setCursor(0, 1);
    lcd.print(s.notes[idx]); lcd.print(" Hz  "); lcd.print(s.name); lcd.print("  ");

    Serial.print(distance); Serial.print("cm  ");
    Serial.print(s.names[idx]); Serial.print("  "); Serial.print(s.notes[idx]); Serial.println("Hz");
  } else {
    noTone(buzzerPin);
    clearStrip();
    lcd.setCursor(0, 0);
    if (thereminOn) {
      lcd.print("Move hand...    ");
      lcd.setCursor(0, 1);
      lcd.print(s.name); lcd.print("            ");
    } else {
      lcd.print("Theremin  OFF   ");
      lcd.setCursor(0, 1);
      lcd.print("1-5: pick scale ");
    }
  }

  delay(150);
}
