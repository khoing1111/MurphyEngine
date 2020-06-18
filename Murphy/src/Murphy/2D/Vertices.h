#pragma once

#include "Murphy/Core.h"
#include "Murphy/Graphics/Geometry.h"
#include "SFML/Graphics.hpp"

namespace Murphy::M2D
{
    struct MURPHY_API Vertex
    {
        Murphy::Vector2F Position;
        Murphy::Vector2F TexCoords;
        Murphy::RGBAColor Color;

        Vertex(Murphy::Vector2F position, Murphy::Vector2F texCoords, Murphy::RGBAColor color);
    };

    class MURPHY_API Vertices : public Drawable
    {
    public:
        Vertices() {}
        virtual ~Vertices() {}

        Vertex& operator[](std::size_t index);

        virtual void Draw(Renderer& renderer) const override
        {
        }

    private:
        std::vector<Vertex> m_Vertices;
    };
}
