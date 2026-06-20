@echo off
REM ========================================
REM CS2 Skin Changer - Standalone Builder
REM Build one complete .exe file - no deps!
REM ========================================

setlocal enabledelayedexpansion

echo.
echo =========================================="
echo  CS2 SKIN CHANGER - STANDALONE BUILD
echo =========================================="
echo.

REM Check if Visual Studio is installed
where cl.exe >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Visual Studio not found!
    echo Please install Visual Studio 2022 Community (free) from:
    echo https://visualstudio.microsoft.com/vs/community/
    echo.
    pause
    exit /b 1
)

echo [+] Visual Studio found

REM Check if CMake is installed
where cmake.exe >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found!
    echo Please install CMake from:
    echo https://cmake.org/download/
    echo.
    pause
    exit /b 1
)

echo [+] CMake found

REM Create build directory
if not exist "build" (
    echo [*] Creating build directory...
    mkdir build
)

echo.
echo [*] Step 1/3: Configuring CMake...
call cd build
call cmake -S .. -B . -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    call cd ..
    pause
    exit /b 1
)

echo [+] CMake configuration successful

echo.
echo [*] Step 2/3: Building standalone executable...
echo [*] This may take 2-5 minutes...
call cmake --build . --config Release --parallel 4

if errorlevel 1 (
    echo [ERROR] Build failed!
    call cd ..
    pause
    exit /b 1
)

echo [+] Build successful!

echo.
echo [*] Step 3/3: Verifying executable...

if exist "bin\skinchanger.exe" (
    echo [+] Executable created: bin\skinchanger.exe
    echo.
    for /F "tokens=*" %%A in ('dir /b bin\skinchanger.exe') do (
        for /F "tokens=5" %%B in ('dir bin\skinchanger.exe') do (
            set "size=%%B"
        )
    )
    
    echo.
    echo =========================================="
    echo  BUILD COMPLETE!
    echo =========================================="
    echo.
    echo [+] File: bin\skinchanger.exe
    echo [+] Type: Standalone executable
    echo [+] No dependencies required
    echo.
    echo [*] Usage:
    echo     1. Double-click skinchanger.exe
    echo     2. Wait for CS2 to launch (auto)
    echo     3. Press INSERT to open overlay
    echo     4. Press ESC to exit
    echo.
    echo [*] Ready to use!
    call cd ..
    
    echo.
    echo Press any key to launch skinchanger.exe...
    pause
    
    echo.
    echo [*] Launching...
    .\build\bin\skinchanger.exe
) else (
    echo [ERROR] skinchanger.exe not found in bin directory!
    echo [DEBUG] Directory contents:
    dir bin\
    call cd ..
    pause
    exit /b 1
)
