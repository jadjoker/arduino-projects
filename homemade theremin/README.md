# Homemade Theremin

An Arduino theremin that uses the HC-SR04 ultrasonic sensor to turn hand distance into musical pitch, quantized to a C major scale across 4 octaves.

## Features

- Hand-controlled pitch snapped to C major scale (C3–B6, 28 notes)
- Audio amplifier + speaker for rich sound (passive buzzer in simulation)
- I2C LCD shows current note name and frequency in real-time
- Push button toggles theremin on/off
- Status LED shows when sound is enabled

## Parts

| Component | Qty |
|-----------|-----|
| Arduino UNO R4 WiFi | 1 |
| HC-SR04 ultrasonic sensor | 1 |
| Audio power amplifier module | 1 |
| Speaker (8Ω passive) | 1 |
| I2C LCD 1602 | 1 |
| Push button | 1 |
| Red LED | 1 |
| 220 Ω resistor | 1 |
| Breadboard + jumper wires | — |

## Wiring

### HC-SR04
| HC-SR04 | Arduino |
|---------|---------|
| VCC | 5V |
| GND | GND |
| TRIG | D12 |
| ECHO | D13 |

### Audio amp + speaker
| Amp pin | Connects to |
|---------|-------------|
| VCC | 5V |
| GND | GND |
| IN (signal) | D8 |
| OUT+ / OUT- | Speaker terminals |

### I2C LCD 1602
| LCD | Arduino |
|-----|---------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### Button & LED
| Component | Arduino |
|-----------|---------|
| Button leg 1 | D2 |
| Button leg 2 | GND |
| LED + (via 220 Ω) | D9 |
| LED - | GND |

## Software setup

Install the [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode) for VS Code.

This project has two build environments:

| Environment | Purpose |
|-------------|---------|
| `sim` | Classic Uno — builds firmware for Wokwi simulation |
| `uno_r4_wifi` | R4 WiFi — builds firmware for real hardware upload |

Use **Terminal → Run Task** to choose:
- **Build: Simulate (Uno)** — build for Wokwi, then press play in diagram.json
- **Build: Upload (R4 WiFi)** — build and flash to the real board over USB
- **Build: Both** — build both environments

## How it works

1. The HC-SR04 measures hand distance (5–100 cm).
2. Distance maps to one of 28 notes in the C major scale (C3–B6), so each note zone is ~3.5 cm wide.
3. The amp drives the speaker with the tone signal from D8.
4. The LCD displays the note name and frequency as you move your hand.
5. Press the button to toggle sound on or off.

## Test cases

| Action | Expected |
|--------|----------|
| Power on | LCD shows "Theremin Ready / Press btn to play" |
| Press button | LED turns on, LCD shows "Theremin OFF → active" |
| Hand at ~5 cm | High note (B6, ~1976 Hz) |
| Hand at ~50 cm | Mid note (~D4, ~294 Hz) |
| Hand at ~100 cm | Low note (C3, 131 Hz) |
| Move hand slowly | LCD updates note name and Hz in real-time |
| Remove hand entirely | Tone stops, LCD shows "Move hand..." |
| Press button again | Sound stops, LED off, LCD shows "Theremin OFF" |
