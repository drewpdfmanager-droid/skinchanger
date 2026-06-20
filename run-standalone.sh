#!/bin/bash
# Quick build and run script

echo "Building CS2 Skin Changer Standalone..."

if [ ! -d "build" ]; then
    mkdir build
fi

cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release --parallel 4

if [ -f "bin/skinchanger.exe" ]; then
    echo ""
    echo "[+] Build successful!"
    echo "[+] Running skinchanger.exe..."
    echo ""
    ./bin/skinchanger.exe
else
    echo "[ERROR] Build failed or executable not found!"
    exit 1
fi
