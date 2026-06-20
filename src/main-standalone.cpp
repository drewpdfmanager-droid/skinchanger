#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <tlhelp32.h>
#include "app/application.h"

// Global application instance
Application* g_app = nullptr;
HWND g_gameWindow = nullptr;

// Find CS2 window
HWND FindCS2Window() {
    return FindWindowA(nullptr, "Counter-Strike 2");
}

// Check if CS2 is running
bool IsCS2Running() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    bool found = false;

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (strcmp(pe32.szExeFile, "cs2.exe") == 0) {
                found = true;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return found;
}

// Launch CS2
bool LaunchCS2() {
    std::cout << "[*] Launching Counter-Strike 2..." << std::endl;
    
    // Try Steam launch
    ShellExecuteA(nullptr, "open", "steam://rungameid/730", nullptr, nullptr, SW_SHOW);
    
    // Wait for CS2 to start
    std::cout << "[*] Waiting for CS2 to launch (max 30 seconds)..." << std::endl;
    for (int i = 0; i < 60; i++) {
        if (IsCS2Running()) {
            std::cout << "[+] CS2 is running!" << std::endl;
            Sleep(3000); // Wait 3 more seconds for full load
            return true;
        }
        Sleep(500);
        std::cout << ".";
    }
    
    std::cout << "\n[WARNING] CS2 didn't launch or took too long" << std::endl;
    return false;
}

void PrintBanner() {
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    std::cout << "\n";
    std::cout << "  ╔═══════════════════════════════════════════╗" << std::endl;
    std::cout << "  ║     CS2 SKIN CHANGER v2.0 ADVANCED       ║" << std::endl;
    std::cout << "  ║   Advanced Memory-Based Skin Modifier    ║" << std::endl;
    std::cout << "  ║   Standalone Edition - No Installation   ║" << std::endl;
    std::cout << "  ╚═══════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    PrintBanner();

    // Step 1: Check if CS2 is running
    std::cout << "[STEP 1/3] Checking Counter-Strike 2..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;
    
    if (!IsCS2Running()) {
        std::cout << "[*] CS2 not found, launching..." << std::endl;
        if (!LaunchCS2()) {
            std::cerr << "[ERROR] Failed to launch CS2!" << std::endl;
            std::cout << "\n[*] Please launch CS2 manually from Steam." << std::endl;
            std::cout << "\nPress any key to exit..." << std::endl;
            getchar();
            return 1;
        }
    } else {
        std::cout << "[+] CS2 is already running!" << std::endl;
    }

    // Step 2: Initialize Skin Changer
    std::cout << "\n[STEP 2/3] Initializing Skin Changer..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;
    
    g_app = new Application();
    if (!g_app->Initialize()) {
        std::cerr << "[ERROR] Failed to initialize application" << std::endl;
        std::cout << "\nPress any key to exit..." << std::endl;
        getchar();
        delete g_app;
        return 1;
    }

    // Step 3: Run main application
    std::cout << "\n[STEP 3/3] Running Skin Changer..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;
    std::cout << "\n" << g_app->GetStatus() << std::endl;
    std::cout << "\n[*] Controls:" << std::endl;
    std::cout << "    INSERT - Toggle overlay menu" << std::endl;
    std::cout << "    ESC    - Exit application" << std::endl;
    std::cout << "\n";

    // Run application
    g_app->Run();

    // Cleanup
    std::cout << "\n[*] Cleaning up..." << std::endl;
    g_app->Shutdown();
    delete g_app;
    g_app = nullptr;

    std::cout << "[+] Goodbye!" << std::endl;
    return 0;
}
