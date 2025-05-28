@echo off
setlocal ENABLEEXTENSIONS

REM Define source and destination
set "SOURCE=assets"
set "DEST=romfs"

REM Check if source exists
if not exist "%SOURCE%" (
    echo [ERROR] The folder '%SOURCE%' does not exist.
    exit /b 1
)

REM Create destination if it doesn't exist
if not exist "%DEST%" (
    echo [INFO] The folder '%DEST%' does not exist. Creating it...
    mkdir "%DEST%"
)

REM Copy the 'assets' folder itself (and all contents) into 'data'
echo [INFO] Copying the '%SOURCE%' folder into '%DEST%'...
xcopy "%SOURCE%" "%DEST%\%SOURCE%\" /E /I /Y /H >nul

echo [SUCCESS] The folder '%SOURCE%' has been copied to '%DEST%\%SOURCE%\'.
pause
