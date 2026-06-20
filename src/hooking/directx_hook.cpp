#include "directx_hook.h"
#include <iostream>

ID3D11Device* DirectXHook::pDevice = nullptr;
ID3D11DeviceContext* DirectXHook::pContext = nullptr;

bool DirectXHook::Initialize() {
    std::cout << "[DirectXHook] Initializing..." << std::endl;
    return true;
}

bool DirectXHook::Shutdown() {
    if (pContext) pContext->Release();
    if (pDevice) pDevice->Release();
    return true;
}

ID3D11Device* DirectXHook::GetDevice() {
    return pDevice;
}

ID3D11DeviceContext* DirectXHook::GetContext() {
    return pContext;
}
