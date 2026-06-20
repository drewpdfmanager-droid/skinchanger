#include "launcher.h"
#include <iostream>
#include <windows.h>

bool Launcher::gameRunning = false;

bool Launcher::CheckRequirements() {
    std::cout << "[Launcher] Checking requirements..." << std::endl;
    return true;
}

bool Launcher::LaunchGame() {
    std::cout << "[Launcher] Launching CS2..." << std::endl;
    gameRunning = true;
    return true;
}

bool Launcher::IsGameRunning() {
    return gameRunning;
}
