# Ultrasonic Range Finder

An Arduino-based distance measurement device with an I2C LCD display, RGB zone indicator, toggleable laser aiming aid, and push-button trigger.

## Features

- Real-time distance measurement up to ~5 m via HC-SR04
- 16×2 I2C LCD shows distance (cm) and proximity zone
- RGB LED color-codes the zone: green (FAR), amber (MEDIUM), red (CLOSE), blue (no reading)
- Red laser module acts as an aiming aid, toggled on/off with a push button
- Zone thresholds: CLOSE ≤ 15 cm | MEDIUM 16–40 cm | FAR > 40 cm

---

## Bill of Materials

| # | Component | Qty | Notes | Where to Source |
|---|-----------|-----|-------|-----------------|
| 1 | Arduino Uno R3 | 1 | Official or clone | Amazon, AliExpress, Adafruit, SparkFun |
| 2 | HC-SR04 Ultrasonic Sensor | 1 | 5 V, 2 cm – 400 cm range | Amazon, AliExpress, Adafruit |
| 3 | 16×2 I2C LCD (PCF8574 backpack) | 1 | I2C address 0x27 (try 0x3F if blank) | Amazon, AliExpress |
| 4 | RGB LED (common cathode) | 1 | 5 mm through-hole | Amazon, AliExpress, DigiKey |
| 5 | KY-008 Laser Diode Module | 1 | 5 V, 650 nm red laser — replaces the sim LED | Amazon, AliExpress |
| 6 | Momentary push button | 1 | Standard 6×6 mm tactile switch | Amazon, AliExpress, DigiKey, Mouser |
| 7 | 220 Ω resistor | 3 | For RGB LED (R, G, B channels) | Any electronics pack |
| 8 | Breadboard (half or full size) | 1 | — | Amazon, Adafruit, SparkFun |
| 9 | Jumper wires (M-M) | ~20 | Assorted colors recommended | Amazon, AliExpress |
| 10 | USB-A to USB-B cable | 1 | For programming the Uno | Usually included with Uno |

### Estimated Cost

| Source | Approx. Total |
|--------|--------------|
| AliExpress (budget) | $15 – $25 |
| Amazon | $30 – $50 |
| Adafruit / SparkFun (quality) | $45 – $70 |

> **Tip:** Search AliExpress or Amazon for "Arduino Starter Kit" — most kits include the Uno, breadboard, HC-SR04, resistors, LEDs, and jumper wires in one bundle for ~$15–20.

---

## Wiring

### HC-SR04

| Sensor Pin | Arduino Pin |
|------------|-------------|
| VCC | 5V |
| GND | GND |
| TRIG | D12 |
| ECHO | D13 |

### I2C LCD (16×2)

| LCD Pin | Arduino Pin |
|---------|-------------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### RGB LED (common cathode)

| LED Pin | Via | Arduino Pin |
|---------|-----|-------------|
| R | 220 Ω | D9 |
| G | 220 Ω | D10 |
| B | 220 Ω | D11 |
| COM (–) | — | GND |

### KY-008 Laser Module

| Laser Pin | Arduino Pin |
|-----------|-------------|
| S (signal) | D7 |
| VCC (middle) | 5V |
| – (GND) | GND |

> **Note:** The KY-008 has a built-in current-limiting resistor — no extra resistor needed.

### Push Button

| Button Pin | Arduino Pin |
|------------|-------------|
| Pin 1 | D2 |
| Pin 2 | GND |

> Uses `INPUT_PULLUP` internally — no external pull-up resistor needed.

---

## Software Setup

### Requirements

- [Arduino CLI](https://arduino.github.io/arduino-cli/) or [Arduino IDE 2](https://www.arduino.cc/en/software)
- [Wokwi for VS Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode) (for simulation)

### Libraries

Declared in `platformio.ini` — PlatformIO downloads them automatically on first build:

```
marcoschwartz/LiquidCrystal_I2C@^1.1.4
```

### Compile & Upload

```powershell
# Build
pio run

# Upload (PlatformIO auto-detects the port, or set upload_port in platformio.ini)
pio run --target upload
```

---

## Simulation (Wokwi)

1. Open the project folder in VS Code
2. Press **Ctrl+Shift+B** to compile
3. Open `diagram.json` and click **Start Simulator**

The slider on the HC-SR04 sets the simulated distance. The KY-008 laser is represented by a red LED in simulation.

---

## How It Works

| State | LCD Row 1 | LCD Row 2 | RGB LED | Laser |
|-------|-----------|-----------|---------|-------|
| No reading | `Out of range` | blank | Blue | unchanged |
| FAR (> 40 cm) | `Dist: X cm` | `Zone: FAR` | Green | unchanged |
| MEDIUM (16–40 cm) | `Dist: X cm` | `Zone: MEDIUM` | Amber | unchanged |
| CLOSE (≤ 15 cm) | `Dist: X cm` | `Zone: CLOSE` | Red | unchanged |
| Button pressed | — | `LZR:ON / LZR:OFF` | unchanged | toggled |

---

## Test Cases

| TC | Slider / Distance | Expected LCD | Expected RGB | Expected Laser LED |
|----|-------------------|-------------|-------------|-------------------|
| TC-1 | 100 cm | `Dist: 100 cm` / `Zone: FAR` | Green | State unchanged |
| TC-2 | 41 cm → 40 cm | FAR → MEDIUM boundary | Green → Amber | — |
| TC-3 | 25 cm | `Dist: 25 cm` / `Zone: MEDIUM` | Amber | — |
| TC-4 | 16 cm → 15 cm | MEDIUM → CLOSE boundary | Amber → Red | — |
| TC-5 | 5 cm | `Dist: 5 cm` / `Zone: CLOSE` | Red | — |
| TC-6 | 0 cm / out of range | `Out of range` / blank | Blue | — |
| TC-7 | Any — press button | Row 2 right: `LZR:ON` | unchanged | Turns on solid |
| TC-8 | Any — press button again | Row 2 right: `LZR:OFF` | unchanged | Turns off |

---

## File Structure

```
ultrasonic range finder/
├── ultrasonic range finder.ino   # Main sketch
├── diagram.json                  # Wokwi circuit diagram
├── libraries.txt                 # Wokwi library list
├── wokwi.toml                    # Wokwi VS Code config
├── .vscode/
│   └── tasks.json                # Ctrl+Shift+B build task
└── README.md                     # This file
```

---

## License

MIT — free to use, modify, and distribute.
