@echo off
REM ========================================
REM CS2 Skin Changer - Environment Setup
REM Helps users set up required tools
REM ========================================

setlocal enabledelayedexpansion

echo.
echo =========================================="
echo  CS2 SKIN CHANGER - ENVIRONMENT SETUP
echo =========================================="
echo.

REM Check existing tools
echo [*] Checking for available tools...
echo.

set "tools_found=0"

REM Check CMake
where cmake.exe >nul 2>&1
if errorlevel 1 (
    echo [X] CMake NOT found
) else (
    echo [+] CMake found
    set /a tools_found+=1
    for /f "tokens=*" %%i in ('cmake --version') do (
        echo    %%i
        goto cmake_done
    )
    :cmake_done
)

REM Check Visual Studio
where cl.exe >nul 2>&1
if errorlevel 1 (
    echo [X] Visual Studio MSVC NOT found
) else (
    echo [+] Visual Studio MSVC found
    set /a tools_found+=1
)

REM Check Clang
where clang.exe >nul 2>&1
if errorlevel 1 (
    echo [X] Clang NOT found
) else (
    echo [+] Clang found
    set /a tools_found+=1
)

REM Check GCC
where gcc.exe >nul 2>&1
if errorlevel 1 (
    echo [X] GCC NOT found
) else (
    echo [+] GCC found
    set /a tools_found+=1
)

REM Check Git
where git.exe >nul 2>&1
if errorlevel 1 (
    echo [X] Git NOT found
) else (
    echo [+] Git found
    set /a tools_found+=1
)

echo.
echo [*] Tools found: %tools_found% / 5
echo.

if %tools_found% geq 2 (
    echo [+] You have enough tools to build!
    echo.
    echo Ready to start? Run: build-standalone-universal.bat
    echo.
    pause
    exit /b 0
)

echo [!] You need to install additional tools!
echo.
echo Choose installation option:
echo.
echo 1. Install Visual Studio 2022 Community (Recommended)
echo 2. Install Clang + Ninja
echo 3. Install GCC/MinGW
echo 4. Install CMake only
echo 5. Exit
echo.

set /p choice="Enter your choice (1-5): "

if "%choice%"=="1" goto install_vs
if "%choice%"=="2" goto install_clang
if "%choice%"=="3" goto install_gcc
if "%choice%"=="4" goto install_cmake
if "%choice%"=="5" exit /b 0

echo Invalid choice!
pause
exit /b 1

:install_vs
echo.
echo [*] Opening Visual Studio 2022 download page...
echo [*] Select "Desktop development with C++"
start https://visualstudio.microsoft.com/downloads/
pause
exit /b 0

:install_clang
echo.
echo [*] Opening LLVM download page...
start https://releases.llvm.org/download.html
echo.
echo [*] Opening Ninja download page...
start https://github.com/ninja-build/ninja/releases
pause
exit /b 0

:install_gcc
echo.
echo [*] Opening MinGW-w64 download page...
start https://www.mingw-w64.org/
pause
exit /b 0

:install_cmake
echo.
echo [*] Opening CMake download page...
start https://cmake.org/download/
pause
exit /b 0
