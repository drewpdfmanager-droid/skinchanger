#include "project_builder.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

const std::string ProjectBuilder::REPO_URL = "https://github.com/makcukhome11-jpg/skinchanger.git";
const std::string ProjectBuilder::PROJECT_DIR = "./skinchanger";
const std::string ProjectBuilder::BUILD_DIR = "./skinchanger/build";
const std::string ProjectBuilder::EXE_PATH = "./skinchanger/build/bin/skinchanger.exe";

std::string GetAbsolutePath(const std::string& path) {
    char buffer[MAX_PATH];
    if (GetFullPathNameA(path.c_str(), MAX_PATH, buffer, nullptr)) {
        return std::string(buffer);
    }
    return path;
}

bool ProjectBuilder::CloneRepository() {
    if (fs::exists(PROJECT_DIR)) {
        std::cout << "[*] Project already exists, skipping clone" << std::endl;
        return true;
    }

    std::cout << "[*] Cloning repository..." << std::endl;
    std::string command = "git clone " + REPO_URL + " " + PROJECT_DIR;
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "[ERROR] Failed to clone repository" << std::endl;
        return false;
    }

    std::cout << "[+] Repository cloned successfully" << std::endl;
    return true;
}

bool ProjectBuilder::ConfigureProject() {
    std::cout << "[*] Configuring project with CMake..." << std::endl;

    if (!fs::exists(BUILD_DIR)) {
        fs::create_directories(BUILD_DIR);
    }

    // Get absolute path to source directory (parent of build)
    std::string sourcePath = GetAbsolutePath(PROJECT_DIR);
    std::string buildPath = GetAbsolutePath(BUILD_DIR);

    // Use absolute paths and proper CMake syntax with -S (source) and -B (build) flags
    std::string command = "cmake -S \"" + sourcePath + "\" -B \"" + buildPath + "\" -G \"Visual Studio 17 2022\" -A x64";
    
    std::cout << "[*] Running: " << command << std::endl;
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "[ERROR] CMake configuration failed" << std::endl;
        return false;
    }

    std::cout << "[+] Project configured successfully" << std::endl;
    return true;
}

bool ProjectBuilder::BuildProject() {
    std::cout << "[*] Building project..." << std::endl;
    std::cout << "[*] This may take a few minutes..." << std::endl;

    std::string buildPath = GetAbsolutePath(BUILD_DIR);
    std::string command = "cmake --build \"" + buildPath + "\" --config Release";
    
    std::cout << "[*] Running: " << command << std::endl;
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "[ERROR] Build failed" << std::endl;
        return false;
    }

    std::cout << "[+] Project built successfully" << std::endl;
    return true;
}

std::string ProjectBuilder::GetExecutablePath() {
    return GetAbsolutePath(EXE_PATH);
}

bool ProjectBuilder::ExecutableExists() {
    return fs::exists(EXE_PATH);
}
