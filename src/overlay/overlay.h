#pragma once

class Overlay {
public:
    static bool Initialize();
    static bool Render();
    static bool Shutdown();
    static bool IsVisible();
    static void Toggle();

private:
    static bool visible;
};
