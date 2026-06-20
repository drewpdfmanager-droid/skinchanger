#pragma once
#include <string>

class Launcher {
public:
    static bool CheckRequirements();
    static bool LaunchGame();
    static bool IsGameRunning();

private:
    static bool gameRunning;
};
