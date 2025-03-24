# HardPanel: Wireless Embedded Debug Console

HardPanel is a **wireless debug terminal** for embedded systems. It connects via **Bluetooth (Classic)** to receive real-time UART logs, status updates, and system messages from your microcontroller, and displays them on an **OLED screen**. Think of it as a **hardware serial monitor** — no wires, no laptops near high-voltage boards.

## 🔥 Why HardPanel?
- **Safe**: No USB, no PC near live power systems
- **Portable**: Battery-powered and wireless
- **Universal**: Works with any MCU that can print to UART or SWO
- **Visual**: Live OLED screen to show logs, errors, counters
- **Expandable**: Future plans for CMSIS-DAP, SWO pass-through, and flashing

## 📦 Features (MVP)
- Bluetooth Serial (SPP) connection to PC or embedded UART output
- 128x64 I2C OLED support
- Scrollable log view
- Basic parsing (e.g., `LOG:`, `ERR:`, `STAT:`)
- Simple UI (button to change views/pages)
- Battery-powered with LiPo support
- SWO input pin (future) for pass-through to PC via Bluetooth

## 🛠️ Stack
- **ESP32** (DevKitC, WROOM, or TTGO)
- **ESP-IDF** or PlatformIO (NO Arduino)
- **SSD1306 OLED** (I2C)

## 📅 Roadmap
### Phase 1: UART Log Display (MVP)
- [ ] Bluetooth SPP receiver
- [ ] Log parser and scroll buffer
- [ ] OLED display update loop
- [ ] Button handler for next/prev view

### Phase 2: Extended HUD
- [ ] Page for key/value stats (e.g. `TEMP=31.2`)
- [ ] Minigraphs for 1-2 tracked variables
- [ ] Config file for custom views

### Phase 3: Advanced I/O
- [ ] Add SWO decoder or pass-through
- [ ] CMSIS-DAP over UART (OpenOCD wireless proof-of-concept)
- [ ] Wi-Fi OTA update mode (opt-in)

## 🚀 Use Cases
- HIL (Hardware-in-the-loop) setups
- High-voltage/industrial equipment debug
- Wireless logger for field-deployed devices
- Replace fragile ST-Link + USB UART spaghetti

## 🤘 Built By
Made by an embedded developer tired of burning laptops on test benches.

---
**License:** MIT or BSD-2 (TBD)

