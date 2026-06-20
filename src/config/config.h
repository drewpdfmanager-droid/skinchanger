#pragma once
#include <string>
#include <map>

class Config {
public:
    static bool LoadConfig(const std::string& filename);
    static bool SaveConfig(const std::string& filename);
    static std::string GetValue(const std::string& key, const std::string& defaultValue = "");
    static void SetValue(const std::string& key, const std::string& value);

private:
    static std::map<std::string, std::string> configMap;
};
