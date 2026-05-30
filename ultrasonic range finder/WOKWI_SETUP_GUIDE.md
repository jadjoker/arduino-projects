# Wokwi VS Code Setup Guide

A step-by-step reference for getting any Arduino project running in the Wokwi VS Code simulator. Based on real lessons learned.

---

## Required Files

Every Wokwi project in VS Code needs these files in the **same folder**:

```
your-project/
├── your-project.ino       ← must match folder name exactly
├── diagram.json           ← circuit layout
├── libraries.txt          ← Wokwi library list
├── wokwi.toml             ← simulator config (this guide)
└── .vscode/
    └── tasks.json         ← Ctrl+Shift+B build task
```

> **Critical rule:** The `.ino` filename must match the folder name exactly.
> A folder called `my project` needs `my project.ino` inside it.
> If they don't match you'll get: `Can't open sketch: main file missing`

---

## Step 1 — Install Arduino CLI

Arduino CLI compiles your sketch into the firmware Wokwi needs.

**Install:**
```powershell
winget install ArduinoSA.CLI
```

If `winget` can't find it, search first:
```powershell
winget search "arduino"
# Look for ArduinoSA.CLI in the results
```

**After install, open a new terminal.** If `arduino-cli` still isn't recognized, add it to PATH manually:
```powershell
# Find it first
Get-ChildItem "C:\Program Files" -Recurse -Filter "arduino-cli.exe" | Select-Object FullName

# Add to PATH for current session
$env:PATH += ";C:\Program Files\Arduino CLI"

# Add permanently (run once)
$current = [System.Environment]::GetEnvironmentVariable("Path", "User")
[System.Environment]::SetEnvironmentVariable("Path", "$current;C:\Program Files\Arduino CLI", "User")
# Then restart VS Code for permanent PATH to take effect
```

---

## Step 2 — Install Board Core & Libraries

Run once per board family:

```powershell
arduino-cli core update-index

# Arduino Uno R3 / Nano / Mega (AVR)
arduino-cli core install arduino:avr

# Arduino Uno R4 Minima or R4 WiFi
arduino-cli core install arduino:renesas_uno

# ESP32
arduino-cli core install esp32:esp32
```

Install any libraries your sketch needs:
```powershell
arduino-cli lib install "LiquidCrystal I2C"
arduino-cli lib install "Library Name Here"
```

---

## Step 3 — Compile the Sketch

Replace `[FQBN]` with your board (see table below):

```powershell
arduino-cli compile --fqbn [FQBN] --output-dir build .
```

### Board FQBN Reference

| Board | FQBN | Build output folder |
|-------|------|-------------------|
| Arduino Uno R3 | `arduino:avr:uno` | `build/arduino.avr.uno/` |
| Arduino Nano | `arduino:avr:nano` | `build/arduino.avr.nano/` |
| Arduino Mega 2560 | `arduino:avr:mega` | `build/arduino.avr.mega/` |
| Arduino Uno R4 Minima | `arduino:renesas_uno:unor4minima` | `build/arduino.renesas_uno.unor4minima/` |
| Arduino Uno R4 WiFi | `arduino:renesas_uno:unor4wifi` | `build/arduino.renesas_uno.unor4wifi/` |
| ESP32 Dev Module | `esp32:esp32:esp32` | `build/esp32.esp32.esp32/` |

After compiling, check what files appeared in `build/`:
```powershell
Get-ChildItem -Path build -Recurse
```
The firmware files will be named after your sketch, e.g. `my project.ino.elf` and `my project.ino.hex`.

---

## Step 4 — Create wokwi.toml

```toml
[wokwi]
version = 1
elf = "build/[board-output-folder]/[sketch-name].ino.elf"
firmware = "build/[board-output-folder]/[sketch-name].ino.hex"
```

### Real examples

**Arduino Uno R3, sketch in folder `my project`:**
```toml
[wokwi]
version = 1
elf = "build/arduino.avr.uno/my project.ino.elf"
firmware = "build/arduino.avr.uno/my project.ino.hex"
```

**Arduino Uno R4 WiFi, sketch in folder `sensor demo`:**
```toml
[wokwi]
version = 1
elf = "build/arduino.renesas_uno.unor4wifi/sensor demo.ino.elf"
firmware = "build/arduino.renesas_uno.unor4wifi/sensor demo.ino.hex"
```

> **Note:** The build output goes directly into `build/` — NOT into a subfolder like `build/arduino.avr.uno/`.
> Always check `Get-ChildItem -Path build -Recurse` after compiling to confirm the actual paths.

---

## Step 5 — Create .vscode/tasks.json

This lets you compile with **Ctrl+Shift+B** instead of typing the command every time.

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build (Arduino CLI)",
      "type": "shell",
      "command": "arduino-cli compile --fqbn [FQBN] --output-dir build .",
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": []
    }
  ]
}
```

---

## Step 6 — Create libraries.txt

List any libraries your sketch uses:

```
# Wokwi Library List
# See https://docs.wokwi.com/guides/libraries

LiquidCrystal I2C
Adafruit GFX Library
```

---

## Step 7 — Start the Simulator

1. Press **Ctrl+Shift+B** to compile
2. Open `diagram.json` in VS Code
3. Click **Start Simulator** in the Wokwi panel

---

## Common Errors & Fixes

| Error | Cause | Fix |
|-------|-------|-----|
| `Firmware path must be a string` | `wokwi.toml` missing `elf`/`firmware` fields | Add both fields to `wokwi.toml` |
| `firmware binary not found` | Wrong path in `wokwi.toml` | Run `Get-ChildItem -Path build -Recurse` to find actual filenames |
| `Can't open sketch: main file missing` | `.ino` filename doesn't match folder name | Rename `.ino` to match folder exactly |
| `arduino-cli not recognized` | CLI not on PATH | Add install dir to PATH, open new terminal |
| `No package found matching input criteria` | Wrong winget ID | Use `winget search "arduino"` to find correct ID (`ArduinoSA.CLI`) |
| `No diagram.json file` | File not in project folder | Create `diagram.json` in the same folder as `.ino` |
| Wokwi diagram pin not connecting | Wrong pin name format | Use `uno:7` not `uno:D7` for Arduino Uno digital pins |

---

## diagram.json Pin Naming Cheatsheet (Arduino Uno)

| Pin type | Format | Example |
|----------|--------|---------|
| Digital | `uno:N` | `uno:7`, `uno:12` |
| Analog | `uno:AN` | `uno:A4`, `uno:A5` |
| Power | `uno:5V` | `uno:5V` |
| Ground | `uno:GND.1` | `uno:GND.1` |

> Do **not** use the `D` prefix (e.g. `uno:D7`) — it won't connect.

---

## Workflow Summary

```
1. arduino-cli core install [core]
2. arduino-cli lib install "[Library]"
3. Ctrl+Shift+B  ←  compiles every time you change code
4. Restart Wokwi simulator to pick up new firmware
```
