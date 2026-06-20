# Quick Setup Guide

## Prerequisites

Install these once:

### 1. Visual Studio 2022 Community (FREE)
- Download: https://visualstudio.microsoft.com/vs/community/
- During installation, select:
  - "Desktop development with C++"
  - Windows 11 SDK
  - CMake tools for Windows

### 2. CMake
- Download: https://cmake.org/download/
- Select "Windows x64 Installer"
- During installation: ✅ "Add CMake to the system PATH"

### 3. Counter-Strike 2
- Install from Steam (it's free!)

## Build Standalone Executable

### Option A: Auto Build & Run (Recommended)
```bash
build-all.bat
```

This will:
1. ✅ Configure CMake
2. ✅ Build standalone .exe
3. ✅ Verify the executable
4. ✅ Launch it automatically

### Option B: Manual Build
```bash
mkdir build
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

Executable will be at: `build/bin/skinchanger.exe`

## Usage

1. **Run** `skinchanger.exe`
2. **Wait** for CS2 to launch (automatic)
3. **Press INSERT** to open overlay menu
4. **Select** weapon and skin
5. **Press ESC** to exit

## Troubleshooting

### "CMake not found"
- Restart your computer after installing CMake
- Or add to PATH manually: `C:\Program Files\CMake\bin`

### "Visual Studio not found"
- Install Visual Studio 2022 Community
- Make sure "C++ Desktop Development" is selected

### "CS2 not launching"
- Make sure Steam is installed
- Counter-Strike 2 must be installed
- Run as Administrator

### Build takes too long
- This is normal (2-5 minutes first time)
- Subsequent builds are faster

## Output Files

After successful build:
- **Main executable**: `build/bin/skinchanger.exe`
- **Size**: ~15-25 MB (all-in-one)
- **Zero external dependencies**

## Distribution

You can share `skinchanger.exe` with others:
- No installation needed
- No dependencies to install
- Just download and run!

---

**Enjoy your skins! 🎮**
