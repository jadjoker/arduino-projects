# Homemade Theremin

An Arduino theremin that uses the HC-SR04 ultrasonic sensor to turn hand distance into musical pitch, quantized to a musical scale so you can play real songs.

## How to play

1. **Power on** — the LCD shows "Theremin Ready".
2. **Press the green button** to turn sound on. The red LED lights up.
3. **Hold your hand above the sensor** — move it closer for higher notes, further away for lower notes. The range is 5 cm (highest) to 100 cm (lowest).
4. **Watch the LCD** — it shows the current note name and frequency on line 1, and the active scale on line 2.
5. **Watch the LED strip** — warm red colours mean low notes; cool blue colours mean high notes. More LEDs lit = higher pitch.
6. **Press the button again** to turn sound off.

### Choosing a scale

Press a number key on the keypad to switch scales mid-song:

| Key | Scale | Best for |
|-----|-------|----------|
| 1 | C Major | Pop, folk, classical melodies |
| 2 | Pentatonic | Any melody — very forgiving, hard to sound wrong |
| 3 | Blues | Blues, rock, soulful improvisation |
| 4 | Natural Minor | Sad or dramatic melodies |
| 5 | Chromatic | Full range — every semitone, hardest to play in tune |

The LCD will briefly show the scale name when you switch, then return to showing the current note.

### Tips for playing songs

- Start with **Pentatonic (key 2)** — every note sounds good together so mistakes don't stand out.
- Move your hand **slowly and deliberately** — each note zone is about 3–4 cm wide.
- Use the LCD note name to find your position for a song, then memorise the rough distances.
- **C Major (key 1)** is best for well-known melodies like Happy Birthday, Twinkle Twinkle, and Ode to Joy.

## Features

- 5 selectable scales via keypad (C Major, Pentatonic, Blues, Natural Minor, Chromatic)
- Hand-controlled pitch quantized to scale notes (no out-of-tune sliding)
- Audio amplifier + speaker for rich sound (passive buzzer in simulation)
- WS2812 LED strip — colour and count show pitch in real-time
- I2C LCD shows current note name, frequency, and active scale
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
| WS2812 RGB LED strip | 1 |
| 4×4 membrane keypad | 1 |
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

### WS2812 LED strip
| Strip | Arduino |
|-------|---------|
| VCC | 5V |
| GND | GND |
| DIN | D6 |

### 4×4 Keypad
| Keypad | Arduino |
|--------|---------|
| R1 | D3 |
| R2 | D4 |
| R3 | D5 |
| R4 | D7 |
| C1 | D10 |
| C2 | D11 |
| C3 | A0 |
| C4 | A1 |

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
2. Distance maps to a note in the selected scale — each note zone is roughly 3–5 cm wide depending on scale.
3. The amp drives the speaker with the tone signal from D8.
4. The WS2812 strip lights up proportionally to pitch, shifting from red (low) to blue (high).
5. The LCD shows the note name, frequency, and current scale name.
6. The keypad switches between 5 scales without interrupting play.
7. Press the button to toggle sound on or off.

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
