#pragma once

#include "Bindable.h"
#include "Exceptions.h"

namespace Murphy::DirectX
{
    template<typename V>
    class VertexBuffer : public Bindable
    {
    public:
        VertexBuffer(Renderer& renderer, const V* vertices, const UInt32 verticesSize, UINT slot = 0)
        {
            m_StrutureSize = sizeof(V);
            m_Slot = slot;

            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.CPUAccessFlags = 0u;
            vertexBufferDesc.MiscFlags = 0u;
            vertexBufferDesc.ByteWidth = verticesSize;
            vertexBufferDesc.StructureByteStride = m_StrutureSize;

            D3D11_SUBRESOURCE_DATA vertexSubResourceData = {};
            vertexSubResourceData.pSysMem = vertices;
            HRESULT hr;
            hr = renderer.GetDevice()->CreateBuffer(
                &vertexBufferDesc, &vertexSubResourceData, m_Buffer.GetAddressOf()
            );

            if (FAILED(hr))
                throw UnableToCreateVertexBuffer(hr);
        }

        virtual void Bind(Renderer& renderer) override
        {
            const UINT offset = 0u;
            renderer.GetDeviceContext()->IASetVertexBuffers(m_Slot, 1u, m_Buffer.GetAddressOf(), &m_StrutureSize, &offset);
        }

    private:
        MP_COMPTR<ID3D11Buffer> m_Buffer;
        UINT m_StrutureSize;
        UINT m_Slot;
    };
}

