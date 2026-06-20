@echo off
REM ========================================
REM CS2 Skin Changer - Universal Standalone Builder
REM Auto-detects ANY compiler - NO Visual Studio requirement!
REM ========================================

setlocal enabledelayedexpansion

echo.
echo =========================================="
echo  CS2 SKIN CHANGER - UNIVERSAL BUILD
echo =========================================="
echo.

REM Check if CMake is installed
where cmake.exe >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found!
    echo Please install CMake from: https://cmake.org/download/
    echo.
    pause
    exit /b 1
)

echo [+] CMake found

REM ========================================
REM DETECT AVAILABLE COMPILERS
REM ========================================

set "COMPILER_FOUND=0"
set "COMPILER_GEN="
set "COMPILER_NAME="

REM Check for Visual Studio 2022
where cl.exe >nul 2>&1
if errorlevel 0 (
    echo [+] Visual Studio MSVC found
    set "COMPILER_FOUND=1"
    set "COMPILER_GEN=Visual Studio 17 2022"
    set "COMPILER_NAME=MSVC (Visual Studio)"
    goto build_with_compiler
)

REM Check for Clang
where clang.exe >nul 2>&1
if errorlevel 0 (
    where ninja.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] Clang found + Ninja found
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=Ninja"
        set "COMPILER_NAME=Clang + Ninja"
        set "COMPILER_CLANG=1"
        goto build_with_compiler
    ) else (
        echo [!] Clang found but Ninja NOT found (skipping)
    )
)

REM Check for GCC/MinGW
where gcc.exe >nul 2>&1
if errorlevel 0 (
    echo [+] GCC/MinGW found
    set "COMPILER_FOUND=1"
    set "COMPILER_GEN=Unix Makefiles"
    set "COMPILER_NAME=GCC/MinGW"
    goto build_with_compiler
)

REM If no compiler found
if %COMPILER_FOUND% equ 0 (
    echo.
    echo [ERROR] No compatible compiler found!
    echo.
    echo Available options:
    echo   1. Visual Studio 2022: https://visualstudio.microsoft.com/downloads/
    echo      Select: "Desktop development with C++"
    echo.
    echo   2. Clang + Ninja: 
    echo      Clang: https://releases.llvm.org/download.html
    echo      Ninja: https://github.com/ninja-build/ninja/releases
    echo.
    echo   3. GCC/MinGW: https://www.mingw-w64.org/
    echo.
    pause
    exit /b 1
)

:build_with_compiler

echo.
echo [*] Using: !COMPILER_NAME!
echo.

REM Create build directory
if not exist "build" (
    echo [*] Creating build directory...
    mkdir build
)

echo [*] Step 1/3: Configuring CMake...

cd build

if defined COMPILER_CLANG (
    REM Special handling for Clang
    cmake -S .. -B . -G "!COMPILER_GEN!" ^
        -DCMAKE_C_COMPILER=clang ^
        -DCMAKE_CXX_COMPILER=clang++ ^
        -DCMAKE_BUILD_TYPE=Release
) else (
    REM Standard CMake configuration
    if "!COMPILER_GEN!"=="Unix Makefiles" (
        cmake -S .. -B . -G "!COMPILER_GEN!" -DCMAKE_BUILD_TYPE=Release
    ) else (
        cmake -S .. -B . -G "!COMPILER_GEN!" -A x64 -DCMAKE_BUILD_TYPE=Release
    )
)

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

echo [+] CMake configuration successful

echo.
echo [*] Step 2/3: Building standalone executable...
echo [*] This may take 2-10 minutes...
echo.

if defined COMPILER_CLANG (
    cmake --build . --config Release --parallel 4
) else if "!COMPILER_GEN!"=="Unix Makefiles" (
    cmake --build . --parallel 4
) else (
    cmake --build . --config Release --parallel 4
)

if errorlevel 1 (
    echo [ERROR] Build failed!
    cd ..
    pause
    exit /b 1
)

echo [+] Build successful!

echo.
echo [*] Step 3/3: Verifying executable...

if exist "bin\skinchanger.exe" (
    echo [+] Executable created: bin\skinchanger.exe
    
    echo.
    echo =========================================="
    echo  BUILD COMPLETE!
    echo =========================================="
    echo.
    echo [+] File: bin\skinchanger.exe
    echo [+] Compiler: !COMPILER_NAME!
    echo [+] Type: Standalone executable
    echo [+] No dependencies required
    echo.
    echo [*] Usage:
    echo     1. Double-click skinchanger.exe
    echo     2. Wait for CS2 to launch
    echo     3. Press INSERT to open overlay
    echo     4. Press ESC to exit
    echo.
    echo [*] Ready to use!
    cd ..
    
    echo.
    echo Press any key to launch skinchanger.exe...
    pause
    
    echo.
    echo [*] Launching skinchanger...
    .\build\bin\skinchanger.exe
) else (
    echo [ERROR] skinchanger.exe not found!
    echo [DEBUG] Directory contents:
    dir bin\
    cd ..
    pause
    exit /b 1
)
