#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>

#include "Murphy/Core.h"
#include "Murphy/Graphics/Renderer.h"
#include "Murphy/Platform/Windows/Window.h"

#include "Core.h"

namespace Murphy::DirectX
{
    class MURPHY_API Renderer : public Murphy::Renderer
    {
    public:
        Renderer(Murphy::Window& window)
            : Murphy::Renderer(window) {}

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        ~Renderer() = default;

        virtual bool Init() override
        {
            unsigned int windowWidth = m_Window.GetWidth();
            unsigned int windowHeight = m_Window.GetHeight();

            // Setup Swap chain Description
            DXGI_SWAP_CHAIN_DESC sd = {};
            sd.BufferCount = 1;
            sd.BufferDesc.Width = windowWidth;
            sd.BufferDesc.Height = windowHeight;
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

            // Request to create D3D Devices, Context and Swap Chain
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
                if (FAILED(D3D11CreateDeviceAndSwapChain(
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
                )))
                    return false;
            }

            // Create backbuffer render target
            MP_COMPTR<ID3D11Resource> backBuffer;
            m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
            m_Device->CreateRenderTargetView(
                backBuffer.Get(),
                nullptr,
                &m_RenderTarget
            );

            // Create depth stencil state
            D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
            depthStencilDesc.DepthEnable = true;
            depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
            depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

            MP_COMPTR<ID3D11DepthStencilState> depthStencilState;
            m_Device->CreateDepthStencilState(&depthStencilDesc, depthStencilState.GetAddressOf());

            // Bind depth stencil to output merger
            m_DeviceContext->OMSetDepthStencilState(depthStencilState.Get(), 1u);

            // Create Depth Stencil texture
            MP_COMPTR<ID3D11Texture2D> depthStencilTexture;
            D3D11_TEXTURE2D_DESC textureDesc = {};
            textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            textureDesc.Width = windowWidth;
            textureDesc.Height = windowHeight;
            textureDesc.MipLevels = 1u;
            textureDesc.ArraySize = 1u;
            textureDesc.Format = DXGI_FORMAT_D32_FLOAT;
            textureDesc.SampleDesc.Count = 1u;
            textureDesc.SampleDesc.Quality = 0u;
            textureDesc.Usage = D3D11_USAGE_DEFAULT;

            m_Device->CreateTexture2D(&textureDesc, nullptr, depthStencilTexture.GetAddressOf());

            // Create Depth Stencil View
            D3D11_DEPTH_STENCIL_VIEW_DESC depthStenciViewDesc = {};
            depthStenciViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
            depthStenciViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
            depthStenciViewDesc.Texture2D.MipSlice = 0u;

            m_Device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStenciViewDesc, m_DepthStencilView.GetAddressOf());

            // Bind Render Target and Depth Stencil View to OM state
            m_DeviceContext->OMSetRenderTargets(1u, m_RenderTarget.GetAddressOf(), m_DepthStencilView.Get());

            return true;
        }

        virtual void ClearFrame(const Murphy::RGBAColor& color) override
        {
            m_DeviceContext->ClearRenderTargetView(m_RenderTarget.Get(), color.ToFloatArray().data());
            m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }

        virtual void EndFrame() override
        {
            m_SwapChain->Present(1u, 0u);
        }

        virtual bool Renderer::Draw() override
        {
            // Configure Vieport
            D3D11_VIEWPORT viewport;
            viewport.Width = m_Window.GetWidth();
            viewport.Height = m_Window.GetHeight();
            viewport.MinDepth = 0;
            viewport.MaxDepth = 1;
            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;

            m_DeviceContext->RSSetViewports(1u, &viewport);

            return true;
        }

        ID3D11Device* GetDevice();
        IDXGISwapChain* GetSwapChain();
        ID3D11DeviceContext* GetDeviceContext();
        ID3D11RenderTargetView* GetRenderTargetView();
        ID3D11DepthStencilView* GetDepthStencilView();

    private:
        MP_COMPTR<ID3D11Device> m_Device;
        MP_COMPTR<IDXGISwapChain> m_SwapChain;
        MP_COMPTR<ID3D11DeviceContext> m_DeviceContext;
        MP_COMPTR<ID3D11RenderTargetView> m_RenderTarget;
        MP_COMPTR<ID3D11DepthStencilView> m_DepthStencilView;
    };
}
