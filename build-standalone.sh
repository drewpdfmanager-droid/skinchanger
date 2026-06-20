#!/bin/bash
# Build standalone executable

echo "=========================================="
echo " CS2 Skin Changer - Standalone Builder"
echo "=========================================="
echo ""

if [ ! -d "build" ]; then
    echo "[*] Creating build directory..."
    mkdir build
fi

echo "[*] Generating project with Visual Studio 17 2022..."
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "[ERROR] CMake configuration failed!"
    cd ..
    exit 1
fi

echo ""
echo "[*] Building project (Release - Optimized)..."
cmake --build . --config Release --parallel 4

if [ $? -ne 0 ]; then
    echo "[ERROR] Build failed!"
    cd ..
    exit 1
fi

echo ""
echo "[+] Build completed successfully!"
echo "[+] Executable: ./bin/skinchanger.exe"
echo ""
echo "[*] File size:"
ls -lh bin/skinchanger.exe
cd ..
