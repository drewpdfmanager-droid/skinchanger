#pragma once
#include <windows.h>
#include <cstdint>
#include <vector>
#include <string>

class Memory {
public:
    static bool AttachToProcess(const std::string& processName);
    static bool DetachFromProcess();
    static uintptr_t FindPattern(const std::string& pattern);
    static bool Read(uintptr_t address, void* buffer, size_t size);
    static bool Write(uintptr_t address, const void* buffer, size_t size);
    static uintptr_t GetModuleBase(const std::string& moduleName);

private:
    static HANDLE hProcess;
};
