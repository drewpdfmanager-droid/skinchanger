@echo off
REM Quick build and run

if not exist "build" mkdir build

cd build
echo [*] Configuring...
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64

echo.
echo [*] Building (this may take a minute)...
cmake --build . --config Release

if exist "bin\skinchanger.exe" (
    echo.
    echo [+] Build successful!
    echo [+] Launching...
    echo.
    cd ..
    .\build\bin\skinchanger.exe
) else (
    echo [ERROR] Build failed!
    cd ..
    pause
    exit /b 1
)
