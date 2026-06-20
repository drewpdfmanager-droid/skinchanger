#pragma once
#include <string>
#include <vector>

struct Skin {
    std::string weaponName;
    std::string skinName;
    int quality; // 0-4
    float wear; // 0.0-1.0
};

class SkinChanger {
public:
    static bool Initialize();
    static bool ApplySkin(const Skin& skin);
    static bool RemoveSkin();
    static std::vector<Skin> GetAvailableSkins();

private:
    static Skin currentSkin;
};
