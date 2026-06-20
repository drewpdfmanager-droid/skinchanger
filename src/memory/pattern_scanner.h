#pragma once
#include <cstdint>
#include <string>

class PatternScanner {
public:
    static uintptr_t Scan(const std::string& pattern);
    static bool Compare(const unsigned char* data, const unsigned char* mask, const char* pattern);

private:
    static uintptr_t BaseAddress;
};
