#include "application.h"
#include "../manager/skinchanger_manager.h"
#include "../overlay/overlay.h"
#include "../ui/console.h"
#include <iostream>
#include <windows.h>

Application::Application() : running(false), initialized(false) {}

Application::~Application() {
    Shutdown();
}

bool Application::Initialize() {
    std::cout << "[Application] Initializing..." << std::endl;
    
    Console::Initialize();
    
    if (!SkinChangerManager::Initialize()) {
        std::cerr << "[Application] Failed to initialize SkinChangerManager" << std::endl;
        return false;
    }
    
    if (!Overlay::Initialize()) {
        std::cerr << "[Application] Failed to initialize Overlay" << std::endl;
        return false;
    }
    
    initialized = true;
    return true;
}

void Application::Run() {
    running = true;
    std::cout << "\n[*] Application is running. Press ESC to exit...\n" << std::endl;
    
    while (running) {
        // Check for ESC key
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            std::cout << "[*] ESC pressed, exiting..." << std::endl;
            running = false;
            break;
        }
        
        // Check for INSERT key
        if (GetAsyncKeyState(VK_INSERT) & 0x8000) {
            Overlay::Toggle();
            Sleep(200); // Debounce
        }
        
        Overlay::Render();
        Sleep(16); // ~60 FPS
    }
}

void Application::Shutdown() {
    if (!initialized) return;
    
    std::cout << "\n[Application] Shutting down..." << std::endl;
    Overlay::Shutdown();
    SkinChangerManager::Shutdown();
    initialized = false;
}

std::string Application::GetStatus() {
    return SkinChangerManager::GetStatus();
}
