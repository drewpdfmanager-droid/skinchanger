#pragma once
#include <string>

class SkinChangerManager {
public:
    static bool Initialize();
    static bool Shutdown();
    static bool ApplySkin(const std::string& weapon, const std::string& skin);
    static std::string GetStatus();

private:
    static bool initialized;
};
