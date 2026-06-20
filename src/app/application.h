#pragma once
#include <string>

class Application {
public:
    Application();
    ~Application();
    
    bool Initialize();
    void Run();
    void Shutdown();
    std::string GetStatus();

private:
    bool running;
    bool initialized;
};
