# Master Parts List

SunFounder Arduino UNO R4 WiFi Starter Kit.

## Microcontroller

| Component | Qty | Notes |
|-----------|-----|-------|
| Arduino UNO R4 WiFi | 1 | ARM Cortex-M4, built-in WiFi (WiFiS3 library) |

## Displays

| Component | Qty | Notes |
|-----------|-----|-------|
| I2C LCD 1602 | 1 | I2C address 0x27 (try 0x3F if blank); lib: LiquidCrystal I2C |
| OLED Screen | 1 | SSD1306, 128×64, I2C; lib: Adafruit SSD1306 |
| 7-Segment Display | 1 | Single digit, common cathode |

## Sensors

| Component | Qty | Notes |
|-----------|-----|-------|
| Temperature & Humidity Sensor | 1 | DHT11; lib: DHT sensor library |
| Ultrasonic Module | 1 | HC-SR04; 2–400 cm range |
| PIR Motion Sensor Module | 1 | Passive infrared; digital HIGH on motion |
| Soil Moisture Module | 1 | Analog output; higher value = drier |
| IR Controller + IR Receiver | 1+1 | 38 kHz; lib: IRremote |
| GY-87 10 DOF Module | 1 | MPU6050 (accel/gyro) + HMC5883L (compass) + BMP180 (baro); I2C |
| MPR121 Module | 1 | 12-channel capacitive touch; I2C; lib: Adafruit MPR121 |
| Photoresistor | 1 | Analog; use with 10 kΩ voltage divider |
| Thermistor | 1 | NTC 10 kΩ; analog; use with 10 kΩ voltage divider |
| Tilt Switch | 1 | Digital; acts like a button when tilted |
| Joystick Module | 1 | 2× analog axes (VRX/VRY) + digital button (SW) |

## Actuators & Output

| Component | Qty | Notes |
|-----------|-----|-------|
| 9G Servo | 1 | PWM; lib: Servo |
| Stepper Motor | 1 | 28BYJ-48 (5V, 64-step); use with ULN2003 driver |
| Stepper Motor Driver | 1 | ULN2003 breakout for 28BYJ-48 |
| Motor (DC) | 1 | Use transistor (S8050) or TA6586 H-bridge for direction |
| Fan | 1 | Small DC fan; wire like the motor |
| Pump | 1 | Mini submersible; switch via relay or transistor |
| Relay | 1 | 5V coil; switches mains or high-current loads; use flyback diode |
| Speaker | 1 | 8Ω passive; pair with audio power amplifier module |
| Audio Power Amplifier Module | 1 | Amplifies Arduino PWM audio to drive speaker |
| WS2812 RGB Strip | 1 | Addressable LEDs; 5V data signal; lib: FastLED or Adafruit NeoPixel |
| Passive Buzzer | 1 | Needs tone() or PWM to make sound |
| Active Buzzer | 1 | Buzzes on DC HIGH — no tone() needed |
| RGB LED | 1 | Common cathode; 3× 220 Ω resistors |
| Green LED | 5 | 220 Ω resistor each |
| Red LED | 5 | 220 Ω resistor each |
| Yellow LED | 5 | 220 Ω resistor each |
| Blue LED | 5 | 220 Ω resistor each |
| White LED | 5 | 220 Ω resistor each |

## Input

| Component | Qty | Notes |
|-----------|-----|-------|
| Keypad (4×4 matrix) | 1 | 8-pin ribbon; lib: Keypad |
| Button (large colored) | 4 | Tactile; use INPUT_PULLUP |
| Button (small tactile) | 10 | Use INPUT_PULLUP |
| Potentiometer | 1 | 10 kΩ; analog read 0–1023 |

## ICs

| Component | Qty | Notes |
|-----------|-----|-------|
| TA6586 | 1 | Dual H-bridge motor driver; controls two DC motors with direction |
| 74HC595 | 1 | 8-bit shift register; drives 8 outputs from 3 pins |
| S8050 Transistor (NPN) | 2 | Switch up to 500 mA loads (motors, relays, buzzers) |
| S8550 Transistor (PNP) | 1 | High-side switch |

## Communication

| Component | Qty | Notes |
|-----------|-----|-------|
| MFRC522 RFID Module | 1 | 13.56 MHz; SPI interface; lib: MFRC522 |

## Passive Components

| Component | Qty |
|-----------|-----|
| Resistor 10 Ω | 10 |
| Resistor 100 Ω | 10 |
| Resistor 220 Ω | 30 |
| Resistor 330 Ω | 10 |
| Resistor 1 kΩ | 10 |
| Resistor 2 kΩ | 10 |
| Resistor 5.1 kΩ | 10 |
| Resistor 10 kΩ | 10 |
| Resistor 100 kΩ | 10 |
| Resistor 1 MΩ | 10 |
| 1N4007 Diode | 5 |
| Capacitor 104 pF | 5 |
| Capacitor 10 µF | 5 |

## Misc

| Component | Qty | Notes |
|-----------|-----|-------|
| Breadboard Power Module w/ Battery | 1 | Powers breadboard from battery; 3.3 V / 5 V switch |
| Breadboard | 1 | Half-size |
| Jump Wire M/M | 65 | |
| Jump Wire F/M | 20 | |
| Type-C USB Cable | 1 | For programming the UNO R4 |
| Tube | 1 | For pump/water projects |
