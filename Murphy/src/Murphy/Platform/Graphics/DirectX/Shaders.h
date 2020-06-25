#pragma once

#include "Bindable.h"
#include "Exceptions.h"

namespace Murphy::DirectX
{
    class Shader : public Bindable
    {
    public:
        void LoadBlobFromFile(LPCWSTR fileName)
        {
            HRESULT hr;
            if (FAILED(hr = D3DReadFileToBlob(fileName, m_Blob.GetAddressOf())))
                throw UnableToReadCSOFile(hr);
        }

        const MP_COMPTR<ID3DBlob> GetBlob()
        {
            return m_Blob;
        }

    protected:
        MP_COMPTR<ID3DBlob> m_Blob;
    };

    class VertexShader : public Shader
    {
    public:
        VertexShader(Renderer& renderer, LPCWSTR vertexShaderFileName)
        {
            HRESULT hr;
            LoadBlobFromFile(vertexShaderFileName);
            if (FAILED(hr = renderer.GetDevice()->CreateVertexShader(
                m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(),
                nullptr, m_VertexShader.GetAddressOf())
            ))
                throw UnableToCreateVSShader(hr);

        }

        virtual void Bind(Renderer& renderer) override
        {
            renderer.GetDeviceContext()->VSSetShader(m_VertexShader.Get(), 0, 0);
        }

    private:
        MP_COMPTR<ID3D11VertexShader> m_VertexShader;
    };

    class PixelShader : public Shader
    {
    public:
        PixelShader(Renderer& renderer, LPCWSTR pixelShaderFileName)
        {
            HRESULT hr;
            LoadBlobFromFile(pixelShaderFileName);
            if (FAILED(hr = renderer.GetDevice()->CreatePixelShader(
                m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(),
                nullptr, m_PixelShader.GetAddressOf())
            ))
                throw UnableToCreatePSShader(hr);

        }

        virtual void Bind(Renderer& renderer) override
        {
            renderer.GetDeviceContext()->PSSetShader(m_PixelShader.Get(), 0, 0);
        }

    private:
        MP_COMPTR<ID3D11PixelShader> m_PixelShader;
    };
}