#pragma once
#include <vector>
#include <string>
#include "skinchanger.h"

class SkinDatabase {
public:
    static bool LoadDatabase();
    static std::vector<Skin> GetSkinsForWeapon(const std::string& weapon);
    static std::vector<std::string> GetAllWeapons();

private:
    static std::vector<Skin> database;
};
