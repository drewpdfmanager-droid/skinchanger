#include "inventory_manager.h"
#include <iostream>

std::vector<InventoryItem> InventoryManager::inventory;

bool InventoryManager::LoadInventory() {
    std::cout << "[InventoryManager] Loading inventory..." << std::endl;
    // Load from game memory or file
    return true;
}

std::vector<InventoryItem> InventoryManager::GetInventory() {
    return inventory;
}

bool InventoryManager::AddItem(const InventoryItem& item) {
    inventory.push_back(item);
    return true;
}

bool InventoryManager::RemoveItem(const std::string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == name) {
            inventory.erase(it);
            return true;
        }
    }
    return false;
}
