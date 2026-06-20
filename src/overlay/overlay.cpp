#include "overlay.h"
#include <iostream>

bool Overlay::visible = false;

bool Overlay::Initialize() {
    std::cout << "[Overlay] Initializing overlay..." << std::endl;
    return true;
}

bool Overlay::Render() {
    if (!visible) return true;
    // Render ImGui overlay
    return true;
}

bool Overlay::Shutdown() {
    std::cout << "[Overlay] Shutting down overlay" << std::endl;
    return true;
}

bool Overlay::IsVisible() {
    return visible;
}

void Overlay::Toggle() {
    visible = !visible;
    std::cout << "[Overlay] " << (visible ? "Shown" : "Hidden") << std::endl;
}
