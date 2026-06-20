#pragma once
#include <string>

class AntiCheat {
public:
    static bool EnableStealthMode();
    static bool DisableStealthMode();
    static bool IsStealthEnabled();
    static bool HideFromDetection();

private:
    static bool stealthEnabled;
};
