#!/bin/bash
# CS2 Skin Changer Standalone Builder
# Builds complete .exe with no external dependencies

set -e  # Exit on error

echo ""
echo "=========================================="
echo " CS2 SKIN CHANGER - STANDALONE BUILD"
echo "=========================================="
echo ""

# Check for Visual Studio
if ! command -v cmake &> /dev/null; then
    echo "[ERROR] CMake not found!"
    echo "Please install CMake from: https://cmake.org/download/"
    exit 1
fi

echo "[+] CMake found"
echo ""

# Create build directory
if [ ! -d "build" ]; then
    echo "[*] Creating build directory..."
    mkdir build
fi

echo "[*] Step 1/3: Configuring CMake..."
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "[ERROR] CMake configuration failed!"
    cd ..
    exit 1
fi

echo "[+] CMake configuration successful"
echo ""

echo "[*] Step 2/3: Building standalone executable...
echo "[*] This may take 2-5 minutes..."
cmake --build . --config Release --parallel 4

if [ $? -ne 0 ]; then
    echo "[ERROR] Build failed!"
    cd ..
    exit 1
fi

echo "[+] Build successful!"
echo ""

echo "[*] Step 3/3: Verifying executable..."

if [ -f "bin/skinchanger.exe" ]; then
    echo "[+] Executable created: bin/skinchanger.exe"
    echo ""
    echo "$(ls -lh bin/skinchanger.exe)"
    echo ""
    echo "=========================================="
    echo " BUILD COMPLETE!"
    echo "=========================================="
    echo ""
    echo "[+] File: bin/skinchanger.exe"
    echo "[+] Type: Standalone executable"
    echo "[+] No dependencies required"
    echo ""
    echo "[*] Usage:"
    echo "    1. Double-click skinchanger.exe"
    echo "    2. Wait for CS2 to launch (auto)"
    echo "    3. Press INSERT to open overlay"
    echo "    4. Press ESC to exit"
    echo ""
    cd ..
    
    echo "Press any key to launch skinchanger.exe..."
    read
    echo ""
    echo "[*] Launching..."
    ./build/bin/skinchanger.exe
else
    echo "[ERROR] skinchanger.exe not found!"
    cd ..
    exit 1
fi
