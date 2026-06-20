@echo off
REM CS2 Skin Changer - Standalone Builder
REM This script builds a completely standalone .exe without any dependencies

echo =========================================="
echo  CS2 Skin Changer - Standalone Builder
echo =========================================="
echo.

if not exist "build" (
    echo [*] Creating build directory...
    mkdir build
)

echo [*] Configuring project...
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo [*] Building standalone executable (Release - Optimized)...
cmake --build . --config Release -- /p:Configuration=Release /p:Platform=x64

if errorlevel 1 (
    echo [ERROR] Build failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo [+] Build completed successfully!
echo [+] Executable location: bin\skinchanger.exe
echo.

if exist "bin\skinchanger.exe" (
    echo [+] File size:
    for %%A in ("bin\skinchanger.exe") do (
        echo     %%~zA bytes (%%~ZA bytes)
    )
    echo.
    echo [*] Ready to use!
    echo [*] Press any key to launch...
    pause
    
    echo [*] Launching skinchanger.exe...
    cd ..
    .\build\bin\skinchanger.exe
) else (
    echo [ERROR] skinchanger.exe not found!
    pause
)

cd ..
