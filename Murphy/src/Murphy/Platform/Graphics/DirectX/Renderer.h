#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#include "Murphy/Core.h"
#include "Murphy/Graphics/Renderer.h"
#include "Murphy/Platform/Windows/Window.h"


#define MP_COMPTR Microsoft::WRL::ComPtr

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

            // Bind output render target
            m_DeviceContext->OMSetRenderTargets(1u, m_RenderTarget.GetAddressOf(), nullptr);

            return true;
        }

        virtual void ClearFrame(const Murphy::RGBAColor& color) override
        {
            m_DeviceContext->ClearRenderTargetView(m_RenderTarget.Get(), color.ToFloatArray().data());
        }

        virtual void EndFrame() override
        {
            m_SwapChain->Present(1u, 0u);
        }

        virtual bool Renderer::Draw() const override
        {
            HRESULT hr;
            const UINT stride = sizeof(Murphy::Vertex3F);
            const Murphy::Vertex3F vertices[] =
            {
                {0.0f, 0.5f, 0.0f},
                {0.5f, -0.5f, 0.0f},
                {-0.5f, -0.5f, 0.0f},
            };


            MP_COMPTR<ID3D11Buffer> vertexBuffer;

            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.CPUAccessFlags = 0u;
            vertexBufferDesc.MiscFlags = 0u;
            vertexBufferDesc.ByteWidth = sizeof(vertices);
            vertexBufferDesc.StructureByteStride = stride;

            D3D11_SUBRESOURCE_DATA vertexSubResourceData = {};
            vertexSubResourceData.pSysMem = vertices;

            if (FAILED(hr = m_Device->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, vertexBuffer.GetAddressOf())))
                return false;

            const UINT offset = 0u;
            m_DeviceContext->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);

            // Load Vertex Shader
            MP_COMPTR<ID3D11VertexShader> vertexShader;
            MP_COMPTR<ID3DBlob> blob;
            if (FAILED(hr = D3DReadFileToBlob(L"VertexShader-vs.cso", &blob)))
                return false;

            if (FAILED(hr = m_Device->CreateVertexShader(
                blob->GetBufferPointer(), blob->GetBufferSize(), 
                nullptr, vertexShader.GetAddressOf())
            ))
                return false;

            m_DeviceContext->VSSetShader(vertexShader.Get(), 0, 0);

            // Describe input layout
            MP_COMPTR<ID3D11InputLayout> inputLayout;
            const D3D11_INPUT_ELEMENT_DESC inputElemDesc[] =
            {
                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
            };

            if (FAILED(hr = m_Device->CreateInputLayout(
                inputElemDesc, std::size(inputElemDesc),
                blob->GetBufferPointer(), blob->GetBufferSize(),
                inputLayout.GetAddressOf()
            )))
                return false;

            m_DeviceContext->IASetInputLayout(inputLayout.Get());

            // Load Pixel Shader
            MP_COMPTR<ID3D11PixelShader> pixelShader;
            if (FAILED(hr = D3DReadFileToBlob(L"PixelShader-ps.cso", &blob)))
                return false;

            if (FAILED(hr = m_Device->CreatePixelShader(
                blob->GetBufferPointer(), blob->GetBufferSize(), 
                nullptr, pixelShader.GetAddressOf())
            ))
                return false;

            m_DeviceContext->PSSetShader(pixelShader.Get(), 0, 0);

            // Configure Vieport
            D3D11_VIEWPORT viewport;
            viewport.Width = m_Window.GetWidth();
            viewport.Height = m_Window.GetHeight();
            viewport.MinDepth = 0;
            viewport.MaxDepth = 1;
            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;

            m_DeviceContext->RSSetViewports(1u, &viewport);

            // Set Primitive Topology
            m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            // Draw vertices
            m_DeviceContext->Draw((UINT)std::size(vertices), 0u);

            return true;
        }

    private:
        MP_COMPTR<ID3D11Device> m_Device;
        MP_COMPTR<IDXGISwapChain> m_SwapChain;
        MP_COMPTR<ID3D11DeviceContext> m_DeviceContext;
        MP_COMPTR<ID3D11RenderTargetView> m_RenderTarget;
    };
}
