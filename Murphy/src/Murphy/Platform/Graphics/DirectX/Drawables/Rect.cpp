#include "mppch.h"
#include "Rect.h"

namespace Murphy::DirectX
{
    Rect::Rect(Murphy::Renderer* renderer)
    {
        auto dxRenderer = static_cast<Renderer*>(renderer);
        if (dxRenderer == nullptr)
            throw DirectXRendererRequired();

        auto indexBuffer = GetIndexBuffer(*dxRenderer);
        SetIndexBuffer(indexBuffer);

        m_IAStage = std::make_unique<IAStage<Vertex>>(
            GetVertexBuffer(*dxRenderer),
            indexBuffer,
            GetInputLayout(*dxRenderer),
            D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
         );

        AddBindable(m_IAStage.get());
        AddBindable(GetVertexShader(*dxRenderer).get());
        AddBindable(GetPixelShader(*dxRenderer).get());
    }
}