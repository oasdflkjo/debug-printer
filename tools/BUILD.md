# Build Instructions

## Prerequisites

1. Required tools (already installed):
   - Python 3.7 or newer
   - Git

2. Install ESP-IDF toolchain:
   ```batch
   # Run the installation script
   install.bat
   ```
   This will install ESP-IDF to C:\tools\esp-idf

## Building the Project

1. Set up the ESP-IDF environment (in a new command prompt):
   ```batch
   C:\tools\esp-idf\export.bat
   ```

2. Build the project:
   ```batch
   cd C:\tools\hardpanel
   idf.py build
   ```

3. Flash to ESP32 (replace COM3 with your device port):
   ```batch
   idf.py -p COM3 flash
   ```

4. Monitor the output:
   ```batch
   idf.py monitor
   ```

## Common Issues

- If you get "command not found" for `idf.py`, make sure you've run the ESP-IDF environment setup:
  ```batch
  C:\tools\esp-idf\export.bat
  ```

- If you get permission errors when accessing the serial port:
  1. Open Device Manager
  2. Find your ESP32 under "Ports (COM & LPT)"
  3. Right-click and select "Properties"
  4. Go to "Port Settings" -> "Advanced"
  5. Uncheck "Allow port sharing"

- If you get build errors about missing tools:
  1. Run the ESP-IDF environment setup again
  2. Try running `idf.py fullclean` before building again

## Directory Structure
```
C:\tools\
├── esp-idf\           # ESP-IDF framework and tools
└── hardpanel\         # Your project files
    ├── main\         # Main component
    ├── CMakeLists.txt
    └── BUILD.md
``` 