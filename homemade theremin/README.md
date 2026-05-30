# Homemade Theremin

A simple Arduino theremin-style instrument that uses the HC-SR04 ultrasonic sensor to turn hand distance into musical pitch.

## Features

- Hand-controlled pitch with the ultrasonic sensor
- Passive buzzer plays the tone
- Push button toggles the theremin on/off
- Status LED shows when sound is enabled

## Parts used

- Arduino UNO R4 WiFi
- HC-SR04 ultrasonic sensor
- Passive buzzer
- Push button
- LED
- 220 Ω resistor
- Breadboard
- Jumper wires

## Wiring

| Component | Arduino Pin |
|-----------|-------------|
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| HC-SR04 TRIG | D12 |
| HC-SR04 ECHO | D13 |
| Buzzer + | D8 |
| Buzzer - | GND |
| Push button | D2 |
| Push button other leg | GND |
| LED + (through 220 Ω resistor) | D9 |
| LED - | GND |

## Software Setup

No external libraries required.

### Install PlatformIO

Install the [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode) for VS Code.

### Compile & Upload

```powershell
# Build
pio run

# Upload (PlatformIO auto-detects the port, or set upload_port in platformio.ini)
pio run --target upload
```

## Simulation (Wokwi)

1. Open the project folder in VS Code.
2. Press **Ctrl+Shift+B** to build.
3. Open `diagram.json` and click **Start Simulator**.
4. Move your hand over the HC-SR04 sensor in the simulator to change pitch.

## How it works

- The ultrasonic sensor measures hand distance.
- Distance is mapped to a musical frequency between about 220 Hz and 880 Hz.
- The passive buzzer plays the tone while the project is enabled.
- Press the button to toggle sound on or off.

## Test cases

| Action | Expected behavior |
|--------|-------------------|
| Press button once | LED turns on, theremin becomes active |
| Move hand closer | Pitch rises |
| Move hand farther | Pitch falls |
| Press button again | Sound stops, LED turns off |
| No hand detected | No tone plays |
