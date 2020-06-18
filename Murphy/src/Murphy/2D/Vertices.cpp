#include "mppch.h"
#include "Vertices.h"

namespace Murphy::M2D
{
    Vertex::Vertex(Murphy::Vector2F position, Murphy::Vector2F texCoords, Murphy::RGBAColor color)
        : Position(position), TexCoords(texCoords), Color(color) {}

    Vertex& Vertices::operator[](std::size_t index)
    {
        return m_Vertices[index];
    }
}
