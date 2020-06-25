#pragma once

#include "Bindable.h"

namespace Murphy::DirectX
{
    template<typename C>
    class ConstantBuffer : public Bindable
    {
    public:
        static bool Create(Renderer& renderer, const C& constant, ConstantBuffer* outputBuffer, UINT slot)
        {
            outputBuffer->m_Slot = slot;
            D3D11_BUFFER_DESC constBufferDesc = {};
            constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
            constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            constBufferDesc.MiscFlags = 0u;
            constBufferDesc.ByteWidth = sizeof(constant);
            constBufferDesc.StructureByteStride = 0u;

            D3D11_SUBRESOURCE_DATA constBufferSubResourceData = {};
            constBufferSubResourceData.pSysMem = &constant;

            return SUCCEEDED(renderer.GetDevice()->CreateBuffer(
                &constBufferDesc, &constBufferSubResourceData, outputBuffer->m_Buffer.GetAddressOf()
            ));
        }

        void Update(Renderer& renderer, const C& constant)
        {
            D3D11_MAPPED_SUBRESOURCE mappedSubresource = {};
            if (FAILED(renderer.GetDeviceContext()->Map(
                m_Buffer.Get(), 0u,
                D3D11_MAP_WRITE_DISCARD, 0u,
                &mappedSubresource
            )))
                return false;

            memcpy(mappedSubresource.pData, &constant, sizof(constant));
            renderer.GetDeviceContext()->Unmap(m_Buffer.Get(), 0u);
        }

    protected:
        MP_COMPTR<ID3D11Buffer> m_Buffer;
        UINT m_Slot;
    };

    template<typename C>
    class VertexConstantBuffer : ConstantBuffer<C>
    {
    public:
        static bool Create(Renderer& renderer, const C& constant, VertexConstantBuffer* outputBuffer, UINT slot)
        {
            return ConstantBuffer<C>::Create(renderer, constant, outputBuffer, slot);
        }

        virtual void Bind(Renderer& renderer) override
        {
            renderer.GetDeviceContext()->VSSetConstantBuffers(m_Slot, 1u, m_Buffer.GetAddressOf());
        }
    };

    template<typename C>
    class PixelConstantBuffer : ConstantBuffer<C>
    {
    public:
        static bool Create(Renderer& renderer, const C& constant, PixelConstantBuffer* outputBuffer, UINT slot)
        {
            return ConstantBuffer<C>::Create(renderer, constant, outputBuffer, slot);
        }

        virtual void Bind(Renderer& renderer) override
        {
            renderer.GetDeviceContext()->PSSetConstantBuffers(m_Slot, 1u, m_Buffer.GetAddressOf());
        }
    };
}