#include "memory.h"
#include <tlhelp32.h>
#include <iostream>

HANDLE Memory::hProcess = nullptr;

bool Memory::AttachToProcess(const std::string& processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (std::string(pe32.szExeFile) == processName) {
                hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
                CloseHandle(hSnapshot);
                return hProcess != nullptr;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return false;
}

bool Memory::DetachFromProcess() {
    if (hProcess) {
        CloseHandle(hProcess);
        hProcess = nullptr;
        return true;
    }
    return false;
}

bool Memory::Read(uintptr_t address, void* buffer, size_t size) {
    if (!hProcess) return false;
    SIZE_T bytesRead = 0;
    return ReadProcessMemory(hProcess, (LPVOID)address, buffer, size, &bytesRead) && bytesRead == size;
}

bool Memory::Write(uintptr_t address, const void* buffer, size_t size) {
    if (!hProcess) return false;
    SIZE_T bytesWritten = 0;
    return WriteProcessMemory(hProcess, (LPVOID)address, buffer, size, &bytesWritten) && bytesWritten == size;
}

uintptr_t Memory::GetModuleBase(const std::string& moduleName) {
    if (!hProcess) return 0;
    
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(hProcess));
    if (hSnapshot == INVALID_HANDLE_VALUE) return 0;

    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &me32)) {
        do {
            if (std::string(me32.szModule) == moduleName) {
                CloseHandle(hSnapshot);
                return (uintptr_t)me32.modBaseAddr;
            }
        } while (Module32Next(hSnapshot, &me32));
    }

    CloseHandle(hSnapshot);
    return 0;
}
