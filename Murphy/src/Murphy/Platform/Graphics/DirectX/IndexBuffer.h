#pragma once

#include "Bindable.h"
#include "Exceptions.h"

namespace Murphy::DirectX
{
    class IndexBuffer : public Bindable
    {
    public:
        IndexBuffer(Renderer& renderer, const unsigned short* indices, const UInt32 indicesSize)
        {
            UINT stride = sizeof(unsigned short);
            D3D11_BUFFER_DESC indexBufferDesc = {};
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.CPUAccessFlags = 0u;
            indexBufferDesc.MiscFlags = 0u;
            indexBufferDesc.ByteWidth = indicesSize;
            indexBufferDesc.StructureByteStride = stride;

            m_IndexCount = indicesSize / stride;

            D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
            indexSubresourceData.pSysMem = indices;
            HRESULT hr;
            if (FAILED(hr = renderer.GetDevice()->CreateBuffer(
                &indexBufferDesc, &indexSubresourceData, m_Buffer.GetAddressOf()
            )))
                throw UnableToCreateIndexBuffer(hr);
        }

        virtual void Bind(Renderer& renderer) override
        {
            renderer.GetDeviceContext()->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
        }

        const UINT GetIndexCount() const
        {
            return m_IndexCount;
        }

    private:
        MP_COMPTR<ID3D11Buffer> m_Buffer;
        UINT m_IndexCount;
    };
}