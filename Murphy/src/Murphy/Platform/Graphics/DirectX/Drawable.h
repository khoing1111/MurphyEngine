#pragma once

#include "Murphy/Graphics/Drawable.h"
#include "Exceptions.h"
#include "Bindable.h"
#include "IndexBuffer.h"

namespace Murphy::DirectX
{
    class Drawable : public Murphy::Drawable
    {
    public:
        Drawable() {}
        virtual ~Drawable() = default;

        void AddBindable(Bindable* bindable)
        {
            m_Bindables.push_back(bindable);
        }

        virtual void Draw(Murphy::Renderer* renderer) override
        {
            auto dxRenderer = static_cast<Murphy::DirectX::Renderer*>(renderer);
            if (dxRenderer == nullptr)
                throw DirectXRendererRequired();

            for (Bindable* bindable : m_Bindables)
            {
                bindable->Bind(*dxRenderer);
            }

            if (auto indexBuffer = m_IndexBuffer.lock(); indexBuffer != nullptr)
            {
                auto indexCount = indexBuffer->GetIndexCount();
                dxRenderer->GetDeviceContext()->DrawIndexed(indexCount, 0u, 0u);
            }
            else
            {
                dxRenderer->GetDeviceContext()->Draw(0u, 0u);
            }
        }

    protected:
        void SetIndexBuffer(MP_SPTR<IndexBuffer> indexBuffer)
        {
            m_IndexBuffer = indexBuffer;
        }

    private:
        std::vector<Bindable*> m_Bindables;
        MP_WPTR<IndexBuffer> m_IndexBuffer;
    };
}
