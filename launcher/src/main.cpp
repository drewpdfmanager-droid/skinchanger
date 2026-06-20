#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include "requirements_checker.h"
#include "project_builder.h"
#include <thread>
#include <chrono>

void PrintBanner() {
    std::cout << "\n";
    std::cout << "  ╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "  ║                                                            ║" << std::endl;
    std::cout << "  ║     CS2 SKIN CHANGER - UNIVERSAL LAUNCHER v2.0            ║" << std::endl;
    std::cout << "  ║     Works with ANY compiler - No specific VS required      ║" << std::endl;
    std::cout << "  ║                                                            ║" << std::endl;
    std::cout << "  ║     Автоматическая установка и запуск программы           ║" << std::endl;
    std::cout << "  ║                                                            ║" << std::endl;
    std::cout << "  ╚════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";
}

bool TryCompilerDetection() {
    std::cout << "\n[*] Detecting available compilers..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    // Try to find any available compiler
    std::vector<std::pair<std::string, std::string>> compilers = {
        {"clang.exe", "Clang"},
        {"cl.exe", "Visual Studio MSVC"},
        {"gcc.exe", "GCC"},
        {"clang++.exe", "Clang++"}
    };

    for (const auto& [compiler, name] : compilers) {
        DWORD dwAttrib = GetFileAttributesA(compiler.c_str());
        if (dwAttrib != INVALID_FILE_ATTRIBUTES) {
            std::cout << "[+] Found: " << name << " (" << compiler << ")" << std::endl;
            return true;
        }

        // Also try with 'where' command
        std::string cmd = "where " + compiler + " >nul 2>&1";
        if (system(cmd.c_str()) == 0) {
            std::cout << "[+] Found: " << name << " (" << compiler << ")" << std::endl;
            return true;
        }
    }

    std::cout << "[X] No compiler found!" << std::endl;
    return false;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    PrintBanner();

    // Step 0: Check compiler availability
    std::cout << "[STEP 0/5] Checking compiler availability..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    if (!TryCompilerDetection()) {
        std::cerr << "\n[ERROR] No C++ compiler found on this system!" << std::endl;
        std::cout << "\nДоступные опции:" << std::endl;
        std::cout << "  1. Visual Studio 2022 Community (Recommended)" << std::endl;
        std::cout << "     https://visualstudio.microsoft.com/downloads/" << std::endl;
        std::cout << "     Select: Desktop development with C++" << std::endl;
        std::cout << "\n  2. Clang" << std::endl;
        std::cout << "     https://releases.llvm.org/download.html" << std::endl;
        std::cout << "\n  3. GCC/MinGW-w64" << std::endl;
        std::cout << "     https://www.mingw-w64.org/" << std::endl;
        std::cout << "\nПожалуйста, установите хотя бы один компилятор и запустите лаунчер заново." << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    // Step 1: Check requirements
    std::cout << "\n[STEP 1/5] Checking system requirements..." << std::endl;
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
    std::cout << "\n[STEP 2/5] Downloading project..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    if (!ProjectBuilder::CloneRepository()) {
        std::cerr << "[ERROR] Failed to download project!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    // Step 3: Configure and build
    std::cout << "\n[STEP 3/5] Configuring project (auto-detecting compiler)..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    if (!ProjectBuilder::ConfigureProject()) {
        std::cerr << "[ERROR] Configuration failed!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }

    std::cout << "\n[STEP 4/5] Building project..." << std::endl;
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
    std::cout << "  ╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "  ║                                                            ║" << std::endl;
    std::cout << "  ║              ✓ УСТАНОВКА ЗАВЕРШЕНА!                        ║" << std::endl;
    std::cout << "  ║                                                            ║" << std::endl;
    std::cout << "  ║         Программа будет запущена через 3 секунды...        ║" << std::endl;
    std::cout << "  ║                                                            ║" << std::endl;
    std::cout << "  ║      Следующие запуски будут намного быстрее! ⚡           ║" << std::endl;
    std::cout << "  ║                                                            ║" << std::endl;
    std::cout << "  ╚════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";

    // Wait 3 seconds
    for (int i = 3; i > 0; i--) {
        std::cout << "\r[*] Запуск через " << i << " секунд...";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\r[+] Запускаю программу...                   " << std::endl;

    // Step 5: Launch the application
    std::cout << "\n[STEP 5/5] Launching application..." << std::endl;
    std::cout << "════════════════════════════════════════════" << std::endl;

    std::string exePath = ProjectBuilder::GetExecutablePath();
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    si.cb = sizeof(si);

    if (CreateProcessA(exePath.c_str(), nullptr, nullptr, nullptr,
        FALSE, 0, nullptr, nullptr, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        std::cout << "[+] Программа запущена!" << std::endl;
        std::cout << "\n[*] Лаунчер может быть закрыт." << std::endl;
        return 0;
    } else {
        std::cerr << "[ERROR] Failed to launch application!" << std::endl;
        std::cout << "\nНажми любую клавишу для выхода..." << std::endl;
        getchar();
        return 1;
    }
}
