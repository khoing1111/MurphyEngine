#include "mppch.h"
#include "Shape.h"


namespace Murphy::M2D
{
    void Rect::SetSize(float x, float y)
    {
        m_Size.X = x;
        m_Size.Y = y;
    }

    void Rect::SetSize(Murphy::Vector2F& size)
    {
        m_Size = size;
    }

    Vector2F Rect::GetSize() const
    {
        return m_Size;
    }
}