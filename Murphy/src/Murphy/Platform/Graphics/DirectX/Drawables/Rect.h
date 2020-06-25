#pragma once

#include "Murphy/Platform/Graphics/DirectX/Drawable.h"
#include "Murphy/Platform/Graphics/DirectX/Exceptions.h"
#include "Murphy/Platform/Graphics/DirectX/VertexBuffer.h"
#include "Murphy/Platform/Graphics/DirectX/IndexBuffer.h"
#include "Murphy/Platform/Graphics/DirectX/Shaders.h"
#include "Murphy/Platform/Graphics/DirectX/InputLayout.h"
#include "Murphy/Platform/Graphics/DirectX/IAStage.h"

namespace Murphy::DirectX
{
    class MURPHY_API Rect : public Drawable
    {
    private:
        MP_SPTR<VertexBuffer<Vertex>> s_VertexBuffer;
        MP_SPTR<IndexBuffer> s_IndexBuffer;
        MP_SPTR<VertexShader> s_VertexShader;
        MP_SPTR<PixelShader> s_PixelShader;
        MP_SPTR<InputLayout> s_InputLayout;

        MP_SPTR<VertexBuffer<Vertex>> GetVertexBuffer(Renderer& renderer)
        {
            if (s_VertexBuffer == nullptr)
            {
                const Vertex vertices[] =
                {
                    {-0.5f, 0.5f, -0.5f, Murphy::Color::Red},
                    {0.5f, 0.5f, -0.5f, Murphy::Color::Green},
                    {0.5f, -0.5f, -0.5f, Murphy::Color::Blue},
                    {-0.5f, -0.5f, -0.5f, Murphy::Color::Red},
                    {-0.5f, 0.5f, 0.5f, Murphy::Color::Green},
                    {0.5f, 0.5f, 0.5f, Murphy::Color::Blue},
                    {0.5f, -0.5f, 0.5f, Murphy::Color::Red},
                    {-0.5f, -0.5f, 0.5f, Murphy::Color::Green},
                };

                s_VertexBuffer = std::make_shared<VertexBuffer<Vertex>>(renderer, vertices, sizeof(vertices));
            }

            return s_VertexBuffer;
        }

        MP_SPTR<IndexBuffer> GetIndexBuffer(Renderer& renderer)
        {
            if (s_IndexBuffer == nullptr)
            {
                const unsigned short indices[] =
                {
                    0, 1, 2, 0, 2, 3,
                    6, 5, 4, 7, 6, 4,
                    1, 5, 2, 5, 6, 2,
                    0, 3, 7, 0, 7, 4,
                    4, 5, 0, 5, 1, 0,
                    2, 6, 3, 6, 7, 3
                };


                s_IndexBuffer = std::make_shared<IndexBuffer>(renderer, indices, sizeof(indices));
            }

            return s_IndexBuffer;
        }

        MP_SPTR<VertexShader> GetVertexShader(Renderer& renderer)
        {
            if (s_VertexShader == nullptr)
            {
                s_VertexShader = std::make_shared<VertexShader>(renderer, L"VertexShader-vs.cso");
            }

            return s_VertexShader;
        }

        MP_SPTR<PixelShader> GetPixelShader(Renderer& renderer)
        {
            if (s_PixelShader == nullptr)
            {
                s_PixelShader = std::make_shared<PixelShader>(renderer, L"PixelShader-ps.cso");
            }

            return s_PixelShader;
        }

        MP_SPTR<InputLayout> GetInputLayout(Renderer& renderer)
        {
            if (s_InputLayout == nullptr)
            {
                const D3D11_INPUT_ELEMENT_DESC inputElemDesc[] =
                {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
                };

                auto vertexShader = GetVertexShader(renderer);
                s_InputLayout = std::make_shared<InputLayout>(renderer, inputElemDesc, std::size(inputElemDesc), *vertexShader);
            }

            return s_InputLayout;
        }

    public:
        Rect(Murphy::Renderer* renderer);
        virtual ~Rect() = default;

    private:
        MP_UPTR<IAStage<Vertex>> m_IAStage;
    };

}