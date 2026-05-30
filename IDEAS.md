# Project Ideas

Difficulty: ⭐ Beginner | ⭐⭐ Intermediate | ⭐⭐⭐ Advanced

Each idea notes the key parts from the kit and what new skill it introduces.

---

## Fun & Games

| # | Project | Diff | Key Parts | New Skill |
|---|---------|------|-----------|-----------|
| G1 | **Reaction Timer** | ⭐ | LED, button, LCD | `millis()` timing, `random()` |
| G2 | **Simon Says** | ⭐ | 4 colored LEDs, 4 buttons, active buzzer | Game state machine, arrays |
| G3 | **Whack-a-Mole** | ⭐⭐ | 5 LEDs, 5 buttons, LCD | Timing windows, scoring, difficulty |
| G4 | **Keypad Piano** | ⭐ | Keypad, passive buzzer or speaker + amp | Keypad library, frequency lookup table |
| G5 | **Joystick Pong** | ⭐⭐ | Joystick, OLED | OLED graphics, game loop, ADC joystick |
| G6 | **OLED Snake** | ⭐⭐ | Joystick, OLED | Linked-list / array snake body, collision |
| G7 | **Spin-the-Wheel** | ⭐⭐ | Stepper motor, buttons, OLED | Stepper library, deceleration |

---

## Practical & Useful

| # | Project | Diff | Key Parts | New Skill |
|---|---------|------|-----------|-----------|
| P1 | **Digital Thermometer** | ⭐ | DHT11, LCD or OLED, RGB LED | DHT library, float display |
| P2 | **Auto Plant Waterer** | ⭐⭐ | Soil moisture, pump, relay, LCD | Relay switching, pump timing |
| P3 | **PIR Motion Alarm** | ⭐ | PIR sensor, buzzer, LED | PIR wiring, digital interrupt-style read |
| P4 | **RFID Door Lock** | ⭐⭐ | RFID module, servo, LCD, buzzer | SPI, RFID library, UID matching |
| P5 | **Smart Fan** | ⭐⭐ | DHT11 or thermistor, fan, S8050 transistor, pot | PWM motor control via transistor |
| P6 | **Light-Sensitive Lamp** | ⭐ | Photoresistor, WS2812 strip, relay | NeoPixel/FastLED library, analog light sense |
| P7 | **Laser Tripwire Alarm** | ⭐⭐ | Photoresistor, active buzzer, relay, LED | Analog threshold, latching alarm state |
| P8 | **WiFi Weather Station** | ⭐⭐⭐ | DHT11, OLED, UNO R4 WiFi | WiFiS3 library, HTTP server or MQTT push |
| P9 | **Soil Monitor + WiFi Log** | ⭐⭐⭐ | Soil moisture, DHT11, UNO R4 WiFi | HTTP POST, time-stamped data logging |

---

## Creative & Audio

| # | Project | Diff | Key Parts | New Skill |
|---|---------|------|-----------|-----------|
| A1 | **Theremin v2** | ⭐⭐ | Ultrasonic, potentiometer, speaker, amp module | Audio amp wiring, analog volume mapping |
| A2 | **Keypad Drum Machine** | ⭐⭐ | Keypad, speaker, amp module | Custom tone synthesis, beat patterns |
| A3 | **Capacitive Drum Pad** | ⭐⭐ | MPR121, speaker, amp module | MPR121/I2C touch library |
| A4 | **WS2812 Color Organ** | ⭐⭐ | WS2812 strip, microphone (or analog from amp) | FastLED/NeoPixel, audio envelope detection |
| A5 | **Gyro Light Show** | ⭐⭐ | GY-87 IMU, WS2812 strip | I2C IMU (MPU6050), Euler angles → color |
| A6 | **OLED Gyro Visualizer** | ⭐⭐ | GY-87, OLED | IMU + OLED graphics, horizon/bubble display |
| A7 | **IR Music Box** | ⭐⭐ | IR controller, IR receiver, speaker, amp | IRremote library, melody lookup by key |
| A8 | **Servo Turret** | ⭐⭐ | Servo, ultrasonic, joystick, OLED | Servo library, sensor + actuator combos |
| A9 | **Stepper Clock Hand** | ⭐⭐⭐ | Stepper motor + driver, OLED | Precise step counting, sweep animation |

---

## Workflow Checklist

When starting any new project:

- [ ] Pick an idea, write one-sentence description + wow factor
- [ ] Copy `_template/` → new folder, rename folder + `.ino` + `wokwi.toml` paths to match
- [ ] Cross-reference `PARTS.md` — note what you need
- [ ] Build the circuit in `diagram.json` (Wokwi)
- [ ] Write code + README side-by-side
- [ ] Simulate with Wokwi, run through test cases
- [ ] Wire it up physically and upload
