@echo off
REM CS2 Skin Changer Build Script

echo ========================================
echo  CS2 Skin Changer Builder
echo ========================================
echo.

if not exist "build" (
    echo [*] Creating build directory...
    mkdir build
)

echo [*] Generating Visual Studio project...
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    pause
    exit /b 1
)

echo.
echo [*] Building project (Release)...
cmake --build . --config Release

if errorlevel 1 (
    echo [ERROR] Build failed!
    pause
    exit /b 1
)

echo.
echo [+] Build completed successfully!
echo [+] Executable: bin\skinchanger.exe
pause
