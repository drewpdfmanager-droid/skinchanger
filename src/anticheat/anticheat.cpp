#include "anticheat.h"
#include <iostream>

bool AntiCheat::stealthEnabled = false;

bool AntiCheat::EnableStealthMode() {
    std::cout << "[AntiCheat] Stealth mode enabled" << std::endl;
    stealthEnabled = true;
    return true;
}

bool AntiCheat::DisableStealthMode() {
    std::cout << "[AntiCheat] Stealth mode disabled" << std::endl;
    stealthEnabled = false;
    return true;
}

bool AntiCheat::IsStealthEnabled() {
    return stealthEnabled;
}

bool AntiCheat::HideFromDetection() {
    if (!stealthEnabled) return false;
    return true;
}
