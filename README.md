# CS2 Skin Changer - Advanced Version

> **Advanced in-game skin modification tool with overlay interface**

## 🎮 Features

✅ **In-Game Overlay Menu** (Press INSERT to toggle)  
✅ **Inventory Management** - View and manage your items  
✅ **Real-Time Skin Application** - Change skins instantly  
✅ **Auto-Launcher** - Automatic system check and CS2 launch  
✅ **Advanced Configuration** - Save/load custom profiles  
✅ **Stealth Mode** - Anti-detection protection  
✅ **DirectX Hooking** - Seamless integration with game  
✅ **Multi-Injection Methods** - Direct Write, VTable Hook, Function Hook  

## 🚀 Quick Start

### Requirements

- Windows 10/11 (64-bit)
- DirectX 11
- Visual C++ Runtime 2019+
- Counter-Strike 2 installed
- Admin rights for launching

### Installation

1. **Download** the latest release
2. **Extract** to any folder
3. **Run** `launcher.exe`
4. **Press INSERT** to open overlay menu

### Usage

```
[*] Launch launcher.exe
[*] System will check requirements
[*] Program auto-builds and launches
[*] Press INSERT to open menu
[*] Select weapon and skin
[*] Skin applies in real-time
[*] Press ESC to close program
```

## 📋 Controls

| Key | Action |
|-----|--------|
| INSERT | Toggle overlay menu |
| ESC | Exit application |
| Click weapon | Select weapon |
| Click skin | Apply skin |

## 🔧 Build Instructions

### Using Launcher (Easiest)
```
launcher.exe
```

### Manual Build
```bash
mkdir build
cd build
cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## 📝 License

MIT License - See LICENSE file

## ⚠️ Disclaimer

This tool is for educational purposes only. Use at your own risk.
