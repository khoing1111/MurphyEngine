#pragma once

#include "Bindable.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"

namespace Murphy::DirectX
{
    template<typename V>
    class IAStage : public Bindable
    {
    public:
        IAStage(MP_SPTR<VertexBuffer<V>> vertexBuffer, MP_SPTR<IndexBuffer> indexBuffer, MP_SPTR<InputLayout> inputLayout, D3D11_PRIMITIVE_TOPOLOGY primitiveTopology)
            : m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer), m_InputLayout(inputLayout), m_PrimitiveTopology(primitiveTopology)
        {
        }

        virtual void Bind(Renderer& renderer) override
        {
            m_VertexBuffer->Bind(renderer);
            m_IndexBuffer->Bind(renderer);
            m_InputLayout->Bind(renderer);
            renderer.GetDeviceContext()->IASetPrimitiveTopology(m_PrimitiveTopology);
        }

    private:
        MP_SPTR<VertexBuffer<V>> m_VertexBuffer;
        MP_SPTR<InputLayout> m_InputLayout;
        MP_SPTR<IndexBuffer> m_IndexBuffer;
        D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;
    };
}

