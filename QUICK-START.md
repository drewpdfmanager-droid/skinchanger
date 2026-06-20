# CS2 Skin Changer - Quick Start Guide

## 🚀 FASTEST WAY TO START

Just run one of these scripts and let it do everything automatically:

### Windows:
```batch
build-standalone-universal.bat
```

### Linux/Mac:
```bash
./build-standalone.sh
```

---

## 📋 What Each Script Does

### `build-standalone-universal.bat` (RECOMMENDED)
- ✅ Auto-detects your compiler (Visual Studio, Clang, GCC)
- ✅ Works WITHOUT specific Visual Studio version requirement
- ✅ Auto-builds and runs
- ✅ Gives you a portable .exe file

### `launcher.exe`
- ✅ One-click setup (if you want pre-built)
- ✅ Auto-checks all requirements
- ✅ Auto-downloads and builds
- ✅ Launches automatically

### `setup-environment.bat`
- ✅ Checks what tools you have installed
- ✅ Helps install missing components
- ✅ Useful if you get errors

---

## 💻 Supported Compilers

| Compiler | Support | Notes |
|----------|---------|-------|
| **Visual Studio 2022** | ✅ Full | Recommended |
| **Visual Studio 2019** | ✅ Full | Works great |
| **Clang** | ✅ Full | Fast compilation |
| **GCC/MinGW** | ✅ Full | Open source option |

---

## ⚡ Quick Install Guide

### Option 1: Automatic (EASIEST)
```batch
build-standalone-universal.bat
```
That's it! The script will:
1. Find your compiler automatically
2. Build the project
3. Launch the program
4. You're ready to use it!

### Option 2: Manual
```batch
mkdir build
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
.\bin\skinchanger.exe
```

### Option 3: With Setup Helper
```batch
setup-environment.bat
REM Follow the prompts, then run:
build-standalone-universal.bat
```

---

## 🎮 Usage

After successful build:
1. **Press INSERT** to open overlay menu
2. **Select weapon** from list
3. **Select skin** you want to apply
4. **Press ESC** to close program

---

## 🆘 Troubleshooting

### "Compiler not found"
```
Run: setup-environment.bat
Install one of the supported compilers above
Run: build-standalone-universal.bat again
```

### "CMake not found"
```
Install from: https://cmake.org/download/
Add to PATH (usually automatic)
Run: build-standalone-universal.bat again
```

### Build takes too long
```
This is normal for first build (5-10 minutes)
Next builds will be much faster (30-60 seconds)
```

### "Cannot find executable"
```
Make sure build directory exists:
  - Look in: project_directory\build\bin\
  - File should be: skinchanger.exe
```

---

## 📁 Project Structure

```
skinchanger/
├── build-standalone-universal.bat  ← Run this first!
├── setup-environment.bat            ← If you have issues
├── CMakeLists-Universal.txt        ← Multi-compiler config
├── README-UNIVERSAL.md             ← Full documentation
├── launcher/                        ← Pre-built launcher
└── src/                            ← Source code
```

---

## ✅ Verification

After building, check if the executable exists:

```batch
dir build\bin\skinchanger.exe
```

If you see it, you're ready to go! 🎉

---

## 🔧 Advanced Options

### Force specific compiler:

**Visual Studio:**
```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
```

**Clang + Ninja:**
```bash
cmake -S . -B build -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

**GCC/MinGW:**
```bash
cmake -S . -B build -G "Unix Makefiles"
```

---

## ⚠️ Disclaimer

This tool is for educational purposes only. Use at your own risk.

---

**Ready? Just run `build-standalone-universal.bat` and let it work!** 🚀
