#pragma once
#include <string>

class InjectionEngine {
public:
    enum InjectionMethod {
        DIRECT_WRITE = 0,
        VTABLE_HOOK = 1,
        FUNCTION_HOOK = 2,
        TRAMPOLINE = 3
    };

    static bool Initialize(InjectionMethod method);
    static bool Inject();
    static bool Eject();
    static InjectionMethod GetCurrentMethod();

private:
    static InjectionMethod currentMethod;
};
