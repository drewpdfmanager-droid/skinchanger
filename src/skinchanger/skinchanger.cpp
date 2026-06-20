#include "skinchanger.h"
#include <iostream>

Skin SkinChanger::currentSkin = {};

bool SkinChanger::Initialize() {
    std::cout << "[SkinChanger] Initializing skin changer..." << std::endl;
    return true;
}

bool SkinChanger::ApplySkin(const Skin& skin) {
    std::cout << "[SkinChanger] Applying skin: " << skin.skinName << " to " << skin.weaponName << std::endl;
    currentSkin = skin;
    return true;
}

bool SkinChanger::RemoveSkin() {
    std::cout << "[SkinChanger] Removing applied skins" << std::endl;
    currentSkin = {};
    return true;
}

std::vector<Skin> SkinChanger::GetAvailableSkins() {
    std::vector<Skin> skins;
    // Load skins from database
    return skins;
}
