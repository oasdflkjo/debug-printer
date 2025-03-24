@echo off
echo Setting up VSCode for ESP-IDF development...

:: Check if VSCode is installed
where code >nul 2>&1
if errorlevel 1 (
    echo VSCode is not installed or not in PATH!
    echo Please install VSCode from https://code.visualstudio.com/
    pause
    exit /b 1
)

:: Install ESP-IDF extension
echo Installing ESP-IDF extension...
code --install-extension espressif.esp-idf-extension

echo Done!
echo.
echo Now you can open the project in VSCode and enjoy proper code intelligence.
echo Make sure you have ESP-IDF installed at C:\tools\esp-idf
echo.
pause 