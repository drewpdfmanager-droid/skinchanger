#pragma once
#include <vector>
#include <string>

struct InventoryItem {
    std::string name;
    std::string rarity;
    float wear;
};

class InventoryManager {
public:
    static bool LoadInventory();
    static std::vector<InventoryItem> GetInventory();
    static bool AddItem(const InventoryItem& item);
    static bool RemoveItem(const std::string& name);

private:
    static std::vector<InventoryItem> inventory;
};
