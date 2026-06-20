@echo off
REM ========================================
REM CS2 Skin Changer - Universal Standalone Builder
REM Auto-detects ANY compiler - NO Visual Studio IDE requirement!
REM ========================================

setlocal enabledelayedexpansion

echo.
echo =========================================="
echo  CS2 SKIN CHANGER - UNIVERSAL BUILD v2.1
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
set "USE_NINJA=0"

REM Check for Ninja first (faster)
where ninja.exe >nul 2>&1
if errorlevel 0 (
    echo [+] Ninja found
    
    REM Check for Clang + Ninja
    where clang.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] Clang found
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=Ninja"
        set "COMPILER_NAME=Clang + Ninja"
        set "COMPILER_CLANG=1"
        set "USE_NINJA=1"
        goto build_with_compiler
    )
    
    REM Check for MSVC + Ninja
    where cl.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] MSVC found
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=Ninja"
        set "COMPILER_NAME=MSVC + Ninja"
        set "COMPILER_MSVC=1"
        set "USE_NINJA=1"
        goto build_with_compiler
    )
    
    REM Check for GCC + Ninja
    where gcc.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] GCC found
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=Ninja"
        set "COMPILER_NAME=GCC + Ninja"
        set "USE_NINJA=1"
        goto build_with_compiler
    )
)

REM If Ninja not available, check for other compilers
REM Check for MSVC with NMake
where cl.exe >nul 2>&1
if errorlevel 0 (
    echo [+] MSVC found (will use NMake)
    set "COMPILER_FOUND=1"
    set "COMPILER_GEN=NMake Makefiles"
    set "COMPILER_NAME=MSVC with NMake"
    set "COMPILER_MSVC=1"
    goto build_with_compiler
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

REM Check for Clang alone
where clang.exe >nul 2>&1
if errorlevel 0 (
    echo [+] Clang found (needs Ninja for better performance)
    set "COMPILER_FOUND=1"
    set "COMPILER_GEN=Unix Makefiles"
    set "COMPILER_NAME=Clang"
    set "COMPILER_CLANG=1"
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
    echo   4. MinGW-w64 with Ninja (recommended for speed)
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

REM Configure CMake with appropriate generator
if !USE_NINJA! equ 1 (
    if defined COMPILER_CLANG (
        echo [*] Configuring with Clang + Ninja...
        cmake -S .. -B . -G "Ninja" ^
            -DCMAKE_C_COMPILER=clang ^
            -DCMAKE_CXX_COMPILER=clang++ ^
            -DCMAKE_BUILD_TYPE=Release
    ) else if defined COMPILER_MSVC (
        echo [*] Configuring with MSVC + Ninja...
        cmake -S .. -B . -G "Ninja" ^
            -DCMAKE_C_COMPILER=cl ^
            -DCMAKE_CXX_COMPILER=cl ^
            -DCMAKE_BUILD_TYPE=Release
    ) else (
        echo [*] Configuring with Ninja...
        cmake -S .. -B . -G "Ninja" -DCMAKE_BUILD_TYPE=Release
    )
) else if "!COMPILER_GEN!"=="NMake Makefiles" (
    echo [*] Configuring with MSVC + NMake...
    cmake -S .. -B . -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
) else if "!COMPILER_GEN!"=="Unix Makefiles" (
    echo [*] Configuring with Unix Makefiles...
    cmake -S .. -B . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
)

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    echo.
    echo Troubleshooting:
    echo - Install Ninja: https://github.com/ninja-build/ninja/releases
    echo - Or install proper Visual Studio with C++ workload
    echo - Or install MinGW-w64: https://www.mingw-w64.org/
    echo.
    cd ..
    pause
    exit /b 1
)

echo [+] CMake configuration successful

echo.
echo [*] Step 2/3: Building standalone executable...
echo [*] This may take 2-10 minutes...
echo.

if !USE_NINJA! equ 1 (
    ninja -j 4
) else if "!COMPILER_GEN!"=="NMake Makefiles" (
    nmake
) else (
    cmake --build . --parallel 4
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
    dir bin\ 2>nul || echo (bin directory is empty)
    cd ..
    pause
    exit /b 1
)
