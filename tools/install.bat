@echo off
echo Installing ESP-IDF toolchain for Windows...

:: Create tools directory
if not exist "C:\tools" mkdir "C:\tools"
cd "C:\tools"

:: Clone ESP-IDF
if not exist "C:\tools\esp-idf" (
    echo Cloning ESP-IDF...
    git clone --recursive https://github.com/espressif/esp-idf.git
)

cd esp-idf

:: Install ESP-IDF tools
echo Installing ESP-IDF tools...
install.bat

:: Create environment setup script
echo Creating environment setup script...
echo @echo off > "C:\tools\esp-idf\export.bat"
echo call "C:\tools\esp-idf\export.bat" >> "C:\tools\esp-idf\export.bat"

echo.
echo Installation complete!
echo.
echo To start using ESP-IDF, run:
echo C:\tools\esp-idf\export.bat
echo.
pause 