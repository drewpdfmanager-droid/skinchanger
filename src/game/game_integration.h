#pragma once
#include <windows.h>
#include <string>

class GameIntegration {
public:
    // Game detection
    static bool IsCS2Running();
    static DWORD GetCS2ProcessID();
    static HWND GetCS2Window();
    
    // Auto-launch
    static bool LaunchCS2();
    static bool WaitForCS2Launch(int maxSeconds = 30);
    
    // Process attachment
    static bool AttachToCS2();
    static bool IsAttached();
    
    // Injection
    static bool InjectSkinChanger();
    static bool EjectSkinChanger();
    
private:
    static bool attached;
    static DWORD processID;
};
