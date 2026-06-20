# CS2 Skin Changer - Universal Edition

> **Works with ANY compiler - no Visual Studio requirement!**

## 🎯 Features

✅ **Single executable** - No dependencies required  
✅ **Works with Visual Studio, Clang, GCC, MinGW**  
✅ **Automatic compiler detection**  
✅ **Fast build process**  
✅ **Portable release binary**  

## 🚀 Quick Start

### Option 1: Using Universal Build Script (EASIEST)
```batch
build-standalone-universal.bat
```

The script will:
1. Auto-detect available compiler
2. Download dependencies if needed
3. Build the project
4. Launch automatically

### Option 2: Manual Build

#### Prerequisites (Choose ONE):
- **Visual Studio 2022** (Free Community Edition) + CMake
- **Clang** + CMake + Ninja
- **GCC/MinGW** + CMake
- **LLVM** + CMake

#### Build Steps:
```bash
mkdir build
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
# OR use your compiler:
# cmake -S .. -B . -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build . --config Release
```

## 💻 Supported Compilers

| Compiler | Status | Notes |
|----------|--------|-------|
| Visual Studio 2022 | ✅ Supported | Recommended |
| Visual Studio 2019 | ✅ Supported | Working |
| Clang 16+ | ✅ Supported | Requires Ninja |
| GCC 11+ | ✅ Supported | Full support |
| MinGW-w64 | ✅ Supported | Full support |

## 🔧 Installation Guide

### Visual Studio 2022 (Windows Only)
1. Download: https://visualstudio.microsoft.com/downloads/
2. Select "Desktop development with C++"
3. Install CMake during installation

### Clang (Windows/Linux/Mac)
1. Download: https://releases.llvm.org/download.html
2. Install with PATH enabled
3. Install CMake: https://cmake.org/download/
4. Install Ninja: https://github.com/ninja-build/ninja/releases

### GCC/MinGW (Windows)
1. Download MinGW-w64: https://www.mingw-w64.org/
2. Install CMake: https://cmake.org/download/

## 📋 Build Options

### Using Visual Studio Generator (MSVC)
```batch
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Using Ninja + Clang
```bash
cmake -S . -B build -G "Ninja" \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Using Unix Makefiles + GCC
```bash
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 4
```

## 🎮 Usage

1. Run `skinchanger.exe`
2. Wait for CS2 to launch (automatic)
3. Press **INSERT** to open overlay
4. Select weapon and skin
5. Press **ESC** to exit

## 🆘 Troubleshooting

### "No compiler found"
```
Install one of the supported compilers above and add to PATH
```

### CMake configuration fails
```
1. Update CMake: cmake --version
2. Ensure compiler is in PATH
3. Try manually specifying generator:
   cmake -S . -B build -G "Visual Studio 17 2022"
```

### Build takes too long
```
Add parallel jobs:
cmake --build build --config Release --parallel 8
```

## 📁 Project Structure

```
skinchanger/
├── src/                    # Source code
├── build/                  # Build directory (auto-created)
├── CMakeLists.txt         # Main CMake config
├── CMakeLists-Universal.txt # Multi-compiler version
├── build-standalone-universal.bat  # Smart build script
└── README-UNIVERSAL.md    # This file
```

## 🔨 Compiler Detection Priority

The universal build script checks compilers in this order:
1. Clang (fastest, most portable)
2. GCC/MinGW
3. Visual Studio MSVC (most compatible)

## 📊 Performance

| Compiler | Build Time | Binary Size |
|----------|-----------|-------------|
| MSVC | 2-5 min | ~3-5 MB |
| Clang | 1-3 min | ~2-4 MB |
| GCC | 2-4 min | ~3-5 MB |

## ✅ Verification

After build, verify executable exists:
```bash
ls -la build/bin/skinchanger.exe
# OR on Windows File Explorer
build\bin\skinchanger.exe
```

## 📝 Environment Variables

Optional for advanced users:

```bash
# Force specific compiler
set CC=clang
set CXX=clang++

# Control build
set CMAKE_BUILD_PARALLEL_LEVEL=8
set VERBOSE=1
```

## ⚠️ Disclaimer

This tool is for educational purposes only. Use at your own risk.

---

**Ready to build? Run `build-standalone-universal.bat` and let it do the work!** 🎉
