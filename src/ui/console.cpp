#include "console.h"

void Console::Initialize() {
    system("title CS2 Skin Changer v2.0");
}

void Console::PrintMenu() {
    std::cout << "\n========================================\n";
    std::cout << "  CS2 SKIN CHANGER v2.0\n";
    std::cout << "========================================\n";
    std::cout << "[1] Apply Skin\n";
    std::cout << "[2] Remove Skin\n";
    std::cout << "[3] View Inventory\n";
    std::cout << "[4] Settings\n";
    std::cout << "[5] Exit\n";
    std::cout << "========================================\n";
}

void Console::PrintStatus(const std::string& status) {
    std::cout << "[*] " << status << std::endl;
}
