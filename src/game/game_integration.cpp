#include "game_integration.h"
#include "../memory/memory.h"
#include <tlhelp32.h>
#include <iostream>
#include <thread>
#include <chrono>

bool GameIntegration::attached = false;
DWORD GameIntegration::processID = 0;

bool GameIntegration::IsCS2Running() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    bool found = false;

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (strcmp(pe32.szExeFile, "cs2.exe") == 0) {
                processID = pe32.th32ProcessID;
                found = true;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return found;
}

DWORD GameIntegration::GetCS2ProcessID() {
    return processID;
}

HWND GameIntegration::GetCS2Window() {
    return FindWindowA(nullptr, "Counter-Strike 2");
}

bool GameIntegration::LaunchCS2() {
    std::cout << "[GameIntegration] Launching CS2 from Steam..." << std::endl;
    ShellExecuteA(nullptr, "open", "steam://rungameid/730", nullptr, nullptr, SW_SHOW);
    return true;
}

bool GameIntegration::WaitForCS2Launch(int maxSeconds) {
    std::cout << "[GameIntegration] Waiting for CS2 to launch..." << std::endl;
    
    for (int i = 0; i < maxSeconds * 2; i++) {
        if (IsCS2Running()) {
            std::cout << "[+] CS2 launched successfully (PID: " << processID << ")" << std::endl;
            Sleep(2000); // Wait for full initialization
            return true;
        }
        Sleep(500);
        std::cout << ".";
    }
    
    std::cout << "\n[ERROR] CS2 launch timeout" << std::endl;
    return false;
}

bool GameIntegration::AttachToCS2() {
    if (attached) return true;
    
    std::cout << "[GameIntegration] Attaching to CS2..." << std::endl;
    
    if (!IsCS2Running()) {
        std::cerr << "[ERROR] CS2 is not running" << std::endl;
        return false;
    }
    
    if (!Memory::AttachToProcess("cs2.exe")) {
        std::cerr << "[ERROR] Failed to attach to CS2 process" << std::endl;
        return false;
    }
    
    attached = true;
    std::cout << "[+] Successfully attached to CS2 process" << std::endl;
    return true;
}

bool GameIntegration::IsAttached() {
    return attached;
}

bool GameIntegration::InjectSkinChanger() {
    if (!attached) {
        if (!AttachToCS2()) return false;
    }
    
    std::cout << "[GameIntegration] Injecting skin changer..." << std::endl;
    // Injection logic here
    return true;
}

bool GameIntegration::EjectSkinChanger() {
    std::cout << "[GameIntegration] Ejecting skin changer..." << std::endl;
    attached = false;
    Memory::DetachFromProcess();
    return true;
}
