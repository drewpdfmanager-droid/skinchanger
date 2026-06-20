#include "requirements_checker.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>

bool RequirementsChecker::CheckAll() {
    std::cout << "Checking Visual Studio 2022..." << std::endl;
    if (!CheckVisualStudio()) {
        std::cerr << "[-] Visual Studio 2022 NOT found!" << std::endl;
        return false;
    }
    std::cout << "[+] Visual Studio 2022 found" << std::endl;

    std::cout << "Checking CMake..." << std::endl;
    if (!CheckCMake()) {
        std::cerr << "[-] CMake NOT found!" << std::endl;
        return false;
    }
    std::cout << "[+] CMake found" << std::endl;

    std::cout << "Checking DirectX..." << std::endl;
    if (!CheckDirectX()) {
        std::cerr << "[-] DirectX NOT found!" << std::endl;
        return false;
    }
    std::cout << "[+] DirectX found" << std::endl;

    std::cout << "Checking Git..." << std::endl;
    if (!CheckGit()) {
        std::cerr << "[-] Git NOT found!" << std::endl;
        return false;
    }
    std::cout << "[+] Git found" << std::endl;

    std::cout << "Checking Visual C++ Runtime..." << std::endl;
    if (!CheckVisualCppRuntime()) {
        std::cerr << "[-] Visual C++ Runtime NOT found!" << std::endl;
        return false;
    }
    std::cout << "[+] Visual C++ Runtime found" << std::endl;

    return true;
}

bool RequirementsChecker::CheckVisualStudio() {
    int result = system("where msbuild >nul 2>&1");
    return result == 0;
}

bool RequirementsChecker::CheckCMake() {
    int result = system("where cmake >nul 2>&1");
    return result == 0;
}

bool RequirementsChecker::CheckDirectX() {
    HMODULE hModule = LoadLibraryA("d3d11.dll");
    if (hModule) {
        FreeLibrary(hModule);
        return true;
    }
    return false;
}

bool RequirementsChecker::CheckGit() {
    int result = system("where git >nul 2>&1");
    return result == 0;
}

bool RequirementsChecker::CheckVisualCppRuntime() {
    HMODULE hModule = LoadLibraryA("msvcrt.dll");
    if (hModule) {
        FreeLibrary(hModule);
        return true;
    }
    return false;
}
