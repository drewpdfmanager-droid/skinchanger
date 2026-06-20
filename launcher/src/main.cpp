#include <iostream>
#include <windows.h>
#include "requirements_checker.h"
#include "project_builder.h"
#include <thread>
#include <chrono>

void PrintBanner() {
    std::cout << "\n";
    std::cout << "  ╔═════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "  ║                                                             ║" << std::endl;
    std::cout << "  ║         CS2 SKIN CHANGER - LAUNCHER v1.0                   ║" << std::endl;
    std::cout << "  ║                                                             ║" << std::endl;
    std::cout << "  ║      Автоматическая установка и запуск программы           ║" << std::endl;
    std::cout << "  ║                                                             ║" << std::endl;
    std::cout << "  ╚═════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    PrintBanner();

    // Step 1: Check requirements
    std::cout << "\n[STEP 1/4] Checking system requirements..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    if (!RequirementsChecker::CheckAll()) {
        std::cerr << "\n[ERROR] Some requirements are not met!" << std::endl;
        std::cout << "\nПожалуйста, установите недостающие компоненты и запустите лаунчер заново." << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    std::cout << "\n[+] All requirements met!" << std::endl;

    // Step 2: Clone repository
    std::cout << "\n[STEP 2/4] Downloading project..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    if (!ProjectBuilder::CloneRepository()) {
        std::cerr << "[ERROR] Failed to download project!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    // Step 3: Configure and build
    std::cout << "\n[STEP 3/4] Configuring project..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    if (!ProjectBuilder::ConfigureProject()) {
        std::cerr << "[ERROR] Configuration failed!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    std::cout << "\n[STEP 4/4] Building project..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    if (!ProjectBuilder::BuildProject()) {
        std::cerr << "[ERROR] Build failed!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    // Check if executable exists
    if (!ProjectBuilder::ExecutableExists()) {
        std::cerr << "[ERROR] Executable not found!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    // Success!
    std::cout << "\n" << std::endl;
    std::cout << "  ╔═════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "  ║                                                             ║" << std::endl;
    std::cout << "  ║              ✓ УСТАНОВКА ЗАВЕРШЕНА!                        ║" << std::endl;
    std::cout << "  ║                                                             ║" << std::endl;
    std::cout << "  ║         Программа будет запущена через 3 секунды...        ║" << std::endl;
    std::cout << "  ║                                                             ║" << std::endl;
    std::cout << "  ╚═════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";

    // Wait 3 seconds
    for (int i = 3; i > 0; i--) {
        std::cout << "\r[*] Запуск через " << i << " секунд...";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\r[+] Запускаю программу...                   " << std::endl;

    // Launch the application
    std::string exePath = ProjectBuilder::GetExecutablePath();
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    si.cb = sizeof(si);

    if (CreateProcessA(exePath.c_str(), nullptr, nullptr, nullptr,
        FALSE, 0, nullptr, nullptr, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        std::cout << "[+] Программа запущена!" << std::endl;
        return 0;
    } else {
        std::cerr << "[ERROR] Failed to launch application!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }
}
