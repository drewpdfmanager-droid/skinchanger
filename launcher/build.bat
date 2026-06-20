@echo off
REM CS2 Skin Changer Launcher Builder

echo ========================================
echo  CS2 Skin Changer Launcher Builder
echo  Сборка лаунчера
echo ========================================
echo.

if not exist "build" (
    echo [*] Создаю папку build...
    mkdir build
)

echo [*] Генерирую проект...
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64

if errorlevel 1 (
    echo [ERROR] Ошибка при генерации!
    pause
    exit /b 1
)

echo.
echo [*] Собираю лаунчер (Release)...
cmake --build . --config Release

if errorlevel 1 (
    echo [ERROR] Ошибка при сборке!
    pause
    exit /b 1
)

echo.
echo [+] Сборка успешно завершена!
echo [+] Файл: bin\launcher.exe
pause
