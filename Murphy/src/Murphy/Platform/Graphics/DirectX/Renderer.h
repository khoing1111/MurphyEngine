#pragma once

#include <d3d11.h>

#include "Murphy/Core.h"
#include "Murphy/Graphics/Renderer.h"
#include "Murphy/Platform/Windows/Window.h"

extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}


namespace Murphy::DirectX
{
    class MURPHY_API Renderer : public Murphy::Renderer
    {
    public:
        Renderer(Murphy::Window& window)
            : Murphy::Renderer(window) {}

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        ~Renderer();

        virtual bool Init() override
        {
            // Setup Swap chain Description
            DXGI_SWAP_CHAIN_DESC sd = {};
            sd.BufferCount = 1;
            sd.BufferDesc.Width = m_Window.GetWidth();
            sd.BufferDesc.Height = m_Window.GetHeight();
            sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            sd.BufferDesc.RefreshRate.Numerator = 60;
            sd.BufferDesc.RefreshRate.Denominator = 1;
            sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

            // Anti Aliasing
            sd.SampleDesc.Count = 1;
            sd.SampleDesc.Quality = 0;

            auto window = static_cast<Murphy::Windows::Window*>(&m_Window);
            if (!window)
            {
                MP_CORELOG_ERROR("Invalid window reference. Require Windows Window.");
                return false;
            }

            sd.OutputWindow = window->GetWindowRef();
            sd.Windowed = true;
            sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            sd.Flags = 0;

            const D3D_FEATURE_LEVEL featureLevelsRequested[] = 
            {
                D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
                D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1 
            };

            D3D_FEATURE_LEVEL featureLevelsSupported;
            UINT createServiceflags = 0;
#ifdef MP_DEBUG
            createServiceflags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

            auto hr = D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                createServiceflags,
                featureLevelsRequested,
                _countof(featureLevelsRequested),
                D3D11_SDK_VERSION,
                &sd,
                &m_SwapChain,
                &m_Device,
                &featureLevelsSupported,
                &m_DeviceContext
            );

            // If you request a D3D_FEATURE_LEVEL_11_1 device on a computer with only the Direct3D 11.0 runtime, 
            // D3D11CreateDeviceAndSwapChain immediately exits with E_INVALIDARG
            if (hr == E_INVALIDARG)
            {
                // Request device again, this time without D3D_FEATURE_LEVEL_11_1
                hr = D3D11CreateDeviceAndSwapChain(
                    nullptr,
                    D3D_DRIVER_TYPE_HARDWARE,
                    nullptr,
                    createServiceflags,
                    &featureLevelsRequested[1],
                    _countof(featureLevelsRequested) - 1,
                    D3D11_SDK_VERSION,
                    &sd,
                    &m_SwapChain,
                    &m_Device,
                    &featureLevelsSupported,
                    &m_DeviceContext
                );

                if (FAILED(hr))
                    return false;
            }

            return true;
        }

        virtual void EndFrame() override
        {
            m_SwapChain->Present(1u, 0u);
        }

    private:
        ID3D11Device* m_Device = nullptr;
        IDXGISwapChain* m_SwapChain = nullptr;
        ID3D11DeviceContext* m_DeviceContext = nullptr;
    };
}

