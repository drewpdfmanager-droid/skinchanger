#pragma once
#include <d3d11.h>

class DirectXHook {
public:
    static bool Initialize();
    static bool Shutdown();
    static ID3D11Device* GetDevice();
    static ID3D11DeviceContext* GetContext();

private:
    static ID3D11Device* pDevice;
    static ID3D11DeviceContext* pContext;
};
