#include "mppch.h"
#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace Murphy::DirectX
{
    ID3D11Device* Renderer::GetDevice()
    {
        return m_Device.Get();
    }

    IDXGISwapChain* Renderer::GetSwapChain()
    {
        return m_SwapChain.Get();
    }

    ID3D11DeviceContext* Renderer::GetDeviceContext()
    {
        return m_DeviceContext.Get();
    }

    ID3D11RenderTargetView* Renderer::GetRenderTargetView()
    {
        return m_RenderTarget.Get();
    }

    ID3D11DepthStencilView* Renderer::GetDepthStencilView()
    {
        return m_DepthStencilView.Get();
    }
}