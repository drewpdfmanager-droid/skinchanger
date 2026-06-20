#include "skinchanger_manager.h"
#include "../skinchanger/skinchanger.h"
#include "../skinchanger/skin_database.h"
#include "../injection/injection_engine.h"
#include "../anticheat/anticheat.h"
#include <iostream>

bool SkinChangerManager::initialized = false;

bool SkinChangerManager::Initialize() {
    if (initialized) return true;
    
    std::cout << "[SkinChangerManager] Initializing..." << std::endl;
    
    if (!SkinDatabase::LoadDatabase()) return false;
    if (!SkinChanger::Initialize()) return false;
    if (!InjectionEngine::Initialize(InjectionEngine::DIRECT_WRITE)) return false;
    if (!AntiCheat::EnableStealthMode()) return false;
    
    initialized = true;
    std::cout << "[SkinChangerManager] Successfully initialized" << std::endl;
    return true;
}

bool SkinChangerManager::Shutdown() {
    if (!initialized) return true;
    
    std::cout << "[SkinChangerManager] Shutting down..." << std::endl;
    SkinChanger::RemoveSkin();
    AntiCheat::DisableStealthMode();
    
    initialized = false;
    return true;
}

bool SkinChangerManager::ApplySkin(const std::string& weapon, const std::string& skin) {
    auto skins = SkinDatabase::GetSkinsForWeapon(weapon);
    for (const auto& s : skins) {
        if (s.skinName == skin) {
            return SkinChanger::ApplySkin(s);
        }
    }
    return false;
}

std::string SkinChangerManager::GetStatus() {
    return "[OK] Skin Changer is running";
}
