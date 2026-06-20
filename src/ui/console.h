#pragma once
#include <iostream>

class Console {
public:
    static void Initialize();
    static void PrintMenu();
    static void PrintStatus(const std::string& status);
};
