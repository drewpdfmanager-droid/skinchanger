#include <iostream>
#include <windows.h>
#include "app/application.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "\n";
    std::cout << "  ╔═══════════════════════════════════════════╗" << std::endl;
    std::cout << "  ║     CS2 Skin Changer v2.0 ADVANCED       ║" << std::endl;
    std::cout << "  ║   Advanced Memory-Based Skin Modifier    ║" << std::endl;
    std::cout << "  ║   With Overlay & Inventory Management    ║" << std::endl;
    std::cout << "  ╚═══════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";

    // Create and initialize application
    Application app;
    
    if (!app.Initialize()) {
        std::cerr << "[Main] Failed to initialize application" << std::endl;
        std::cout << "\nPress any key to exit..." << std::endl;
        getchar();
        return 1;
    }

    std::cout << "\n[*] Starting application..." << std::endl;
    std::cout << "[*] Press INSERT to toggle overlay" << std::endl;
    std::cout << "[*] Press ESC to exit" << std::endl;
    std::cout << "\n" << app.GetStatus() << std::endl;
    std::cout << "\n";

    // Run application
    app.Run();

    // Cleanup
    app.Shutdown();

    return 0;
}
