#include "injection_engine.h"
#include <iostream>

InjectionEngine::InjectionMethod InjectionEngine::currentMethod = InjectionEngine::DIRECT_WRITE;

bool InjectionEngine::Initialize(InjectionMethod method) {
    std::cout << "[InjectionEngine] Initializing with method: " << (int)method << std::endl;
    currentMethod = method;
    return true;
}

bool InjectionEngine::Inject() {
    std::cout << "[InjectionEngine] Injecting..." << std::endl;
    return true;
}

bool InjectionEngine::Eject() {
    std::cout << "[InjectionEngine] Ejecting..." << std::endl;
    return true;
}

InjectionEngine::InjectionMethod InjectionEngine::GetCurrentMethod() {
    return currentMethod;
}
