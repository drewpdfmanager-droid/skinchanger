@echo off
REM ========================================
REM CS2 Skin Changer - Universal Standalone Builder
REM Auto-detects ANY compiler - NO Visual Studio IDE requirement!
REM ========================================

setlocal enabledelayedexpansion

echo.
echo =========================================="
echo  CS2 SKIN CHANGER - UNIVERSAL BUILD v3.0
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
set "USE_NMAKE=0"

REM Priority 1: Check for Ninja first (fastest)
where ninja.exe >nul 2>&1
if errorlevel 0 (
    echo [+] Ninja found - PRIORITY 1
    
    REM Check for Clang + Ninja
    where clang.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] Clang found - using Clang + Ninja
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=Ninja"
        set "COMPILER_NAME=Clang + Ninja (FASTEST)"
        set "COMPILER_CLANG=1"
        set "USE_NINJA=1"
        goto build_with_compiler
    )
    
    REM Check for MSVC + Ninja
    where cl.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] MSVC found - using MSVC + Ninja
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=Ninja"
        set "COMPILER_NAME=MSVC + Ninja (FAST)"
        set "COMPILER_MSVC=1"
        set "USE_NINJA=1"
        goto build_with_compiler
    )
    
    REM Check for GCC + Ninja
    where gcc.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] GCC found - using GCC + Ninja
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=Ninja"
        set "COMPILER_NAME=GCC + Ninja (FAST)"
        set "USE_NINJA=1"
        goto build_with_compiler
    )
)

REM Priority 2: Check for MSVC with NMake
where cl.exe >nul 2>&1
if errorlevel 0 (
    echo [+] MSVC found - PRIORITY 2
    where nmake.exe >nul 2>&1
    if errorlevel 0 (
        echo [+] NMake found - using MSVC + NMake
        set "COMPILER_FOUND=1"
        set "COMPILER_GEN=NMake Makefiles"
        set "COMPILER_NAME=MSVC with NMake"
        set "COMPILER_MSVC=1"
        set "USE_NMAKE=1"
        goto build_with_compiler
    ) else (
        echo [!] NMake not found, will try Unix Makefiles
    )
)

REM Priority 3: Check for GCC/MinGW
where gcc.exe >nul 2>&1
if errorlevel 0 (
    echo [+] GCC/MinGW found - PRIORITY 3
    set "COMPILER_FOUND=1"
    set "COMPILER_GEN=Unix Makefiles"
    set "COMPILER_NAME=GCC/MinGW"
    goto build_with_compiler
)

REM Priority 4: Check for Clang alone
where clang.exe >nul 2>&1
if errorlevel 0 (
    echo [+] Clang found - PRIORITY 4
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
    echo Install ONE of these:
    echo.
    echo 1. Visual Studio 2022 Community (Free):
    echo    https://visualstudio.microsoft.com/downloads/
    echo    Select: "Desktop development with C++"
    echo.
    echo 2. Ninja + MSVC (RECOMMENDED - Fastest):
    echo    Ninja: https://github.com/ninja-build/ninja/releases
    echo    Download ninja-win.zip and extract to PATH
    echo.
    echo 3. Clang + Ninja (ALSO FAST):
    echo    Clang: https://releases.llvm.org/download.html
    echo    Ninja: https://github.com/ninja-build/ninja/releases
    echo.
    echo 4. MinGW-w64:
    echo    https://www.mingw-w64.org/
    echo.
    pause
    exit /b 1
)

:build_with_compiler

echo.
echo [*] Compiler: !COMPILER_NAME!
echo.

REM Create build directory
if not exist "build" (
    echo [*] Creating build directory...
    mkdir build
)

REM Clean old build if needed
if exist "build\CMakeCache.txt" (
    echo [*] Cleaning previous build...
    del /q build\CMakeCache.txt >nul 2>&1
    rmdir /s /q build\CMakeFiles >nul 2>&1
)

echo [*] Step 1/3: Configuring CMake...
echo [*] Generator: !COMPILER_GEN!
echo.

cd build

REM Configure CMake with appropriate generator
if !USE_NINJA! equ 1 (
    if defined COMPILER_CLANG (
        echo [*] Setting up Clang compiler...
        cmake -S .. -B . -G "Ninja" ^
            -DCMAKE_C_COMPILER=clang ^
            -DCMAKE_CXX_COMPILER=clang++ ^
            -DCMAKE_BUILD_TYPE=Release
    ) else if defined COMPILER_MSVC (
        echo [*] Setting up MSVC compiler...
        cmake -S .. -B . -G "Ninja" ^
            -DCMAKE_BUILD_TYPE=Release
    ) else (
        echo [*] Setting up compiler with Ninja...
        cmake -S .. -B . -G "Ninja" -DCMAKE_BUILD_TYPE=Release
    )
) else if !USE_NMAKE! equ 1 (
    echo [*] Setting up MSVC with NMake...
    cmake -S .. -B . -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
) else if "!COMPILER_GEN!"=="Unix Makefiles" (
    echo [*] Setting up Unix Makefiles...
    cmake -S .. -B . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
)

if errorlevel 1 (
    echo.
    echo [ERROR] CMake configuration failed!
    echo.
    echo Possible solutions:
    echo 1. Install Ninja for faster builds:
    echo    https://github.com/ninja-build/ninja/releases
    echo.
    echo 2. Add compiler to PATH:
    echo    - For MSVC: Run "Developer Command Prompt for VS"
    echo    - For GCC: Add MinGW bin directory to PATH
    echo.
    echo 3. Install full Visual Studio 2022 with C++ tools
    echo.
    cd ..
    pause
    exit /b 1
)

echo [+] CMake configuration successful
echo.

echo [*] Step 2/3: Building standalone executable...
echo [*] This may take 2-10 minutes on first build...
echo.

if !USE_NINJA! equ 1 (
    echo [*] Compiling with Ninja (parallel)...
    ninja -j 4
) else if !USE_NMAKE! equ 1 (
    echo [*] Compiling with NMake...
    nmake
) else (
    echo [*] Compiling with Make (parallel)...
    cmake --build . --parallel 4
)

if errorlevel 1 (
    echo.
    echo [ERROR] Build failed!
    echo [*] Check the error messages above
    echo.
    cd ..
    pause
    exit /b 1
)

echo.
echo [+] Build successful!
echo.

echo [*] Step 3/3: Verifying executable...

if exist "bin\skinchanger.exe" (
    echo [+] Executable found: bin\skinchanger.exe
    
    echo.
    echo =========================================="
    echo  BUILD COMPLETE AND SUCCESSFUL!
    echo =========================================="
    echo.
    echo [+] File: bin\skinchanger.exe
    echo [+] Compiler: !COMPILER_NAME!
    echo [+] Type: Standalone executable
    echo [+] No runtime dependencies required
    echo.
    echo [*] Controls:
    echo     - INSERT: Toggle overlay menu
    echo     - ESC: Exit program
    echo     - Click to select weapon/skin
    echo.
    echo [*] Ready to use!
    cd ..
    
    echo.
    echo Press any key to launch skinchanger.exe...
    pause
    
    echo.
    echo [*] Launching application...
    .\build\bin\skinchanger.exe
) else (
    echo.
    echo [ERROR] Executable not created!
    echo.
    echo Checking build output:
    dir bin\ 2>nul || (
        echo [!] bin directory not found
        echo [*] Check CMake output above for errors
    )
    cd ..
    pause
    exit /b 1
)
