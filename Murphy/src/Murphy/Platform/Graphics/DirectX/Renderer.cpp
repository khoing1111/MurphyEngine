#include "mppch.h"
#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")

namespace Murphy::DirectX
{
    Renderer::~Renderer()
    {
        if (m_Device != nullptr)
            m_Device->Release();

        if (m_SwapChain != nullptr)
            m_SwapChain->Release();

        if (m_DeviceContext != nullptr)
            m_DeviceContext->Release();
    }
}