#include "skin_database.h"
#include <iostream>

std::vector<Skin> SkinDatabase::database;

bool SkinDatabase::LoadDatabase() {
    std::cout << "[SkinDatabase] Loading skin database..." << std::endl;
    
    // Load default skins
    database.push_back({"AK-47", "Dragon Lore FN", 0, 0.01f});
    database.push_back({"AK-47", "Point Disarray MW", 1, 0.13f});
    database.push_back({"M4A1-S", "Cyrex FN", 0, 0.03f});
    database.push_back({"AWP Dragon Lore", "FN", 0, 0.01f});
    database.push_back({"USP-S", "Kill Confirmed FT", 2, 0.36f});
    database.push_back({"P250", "Undertow FN", 0, 0.04f});
    
    std::cout << "[SkinDatabase] Loaded " << database.size() << " skins" << std::endl;
    return true;
}

std::vector<Skin> SkinDatabase::GetSkinsForWeapon(const std::string& weapon) {
    std::vector<Skin> result;
    for (const auto& skin : database) {
        if (skin.weaponName == weapon) {
            result.push_back(skin);
        }
    }
    return result;
}

std::vector<std::string> SkinDatabase::GetAllWeapons() {
    std::vector<std::string> weapons;
    for (const auto& skin : database) {
        bool found = false;
        for (const auto& w : weapons) {
            if (w == skin.weaponName) {
                found = true;
                break;
            }
        }
        if (!found) {
            weapons.push_back(skin.weaponName);
        }
    }
    return weapons;
}
