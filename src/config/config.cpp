#include "config.h"
#include <iostream>
#include <fstream>

std::map<std::string, std::string> Config::configMap;

bool Config::LoadConfig(const std::string& filename) {
    std::cout << "[Config] Loading config from " << filename << std::endl;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "[Config] Config file not found, creating default" << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            configMap[key] = value;
        }
    }
    file.close();
    return true;
}

bool Config::SaveConfig(const std::string& filename) {
    std::cout << "[Config] Saving config to " << filename << std::endl;
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    for (const auto& pair : configMap) {
        file << pair.first << "=" << pair.second << "\n";
    }
    file.close();
    return true;
}

std::string Config::GetValue(const std::string& key, const std::string& defaultValue) {
    auto it = configMap.find(key);
    return it != configMap.end() ? it->second : defaultValue;
}

void Config::SetValue(const std::string& key, const std::string& value) {
    configMap[key] = value;
}
