#pragma once
#include <string>

class RequirementsChecker {
public:
    static bool CheckAll();
    static bool CheckVisualStudio();
    static bool CheckCMake();
    static bool CheckDirectX();
    static bool CheckGit();
    static bool CheckVisualCppRuntime();
};
