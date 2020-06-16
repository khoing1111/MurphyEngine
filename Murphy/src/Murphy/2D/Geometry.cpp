#include "mppch.h"
#include "Geometry.h"


namespace Murphy::M2D
{
    //------------------------------------------------------------------
    // CLASS TRANSFORMABLE
    void Transformable::SetPosition(float x, float y)
    {
        m_Position.X = x;
        m_Position.Y = y;
    }

    void Transformable::SetPosition(Vector2F& position)
    {
        m_Position = position;
    }

    Vector2F Transformable::GetPosition() const
    {
        return m_Position;
    }

    void Transformable::SetOrigin(float x, float y)
    {
        m_Origin.X = x;
        m_Origin.Y = y;
    }

    void Transformable::SetOrigin(Vector2F& origin)
    {
        m_Origin = origin;
    }

    Vector2F Transformable::GetOrigin() const
    {
        return m_Origin;
    }

    void Transformable::SetRotation(float rotation)
    {
        m_Rotation = rotation;
    }

    float Transformable::GetRotation() const
    {
        return m_Rotation;
    }

    void Transformable::SetScale(float x, float y)
    {
        m_Scale.X = x;
        m_Scale.Y = y;
    }

    void Transformable::SetScale(Vector2F& scale)
    {
        m_Scale = scale;
    }

    Vector2F Transformable::GetScale() const
    {
        return m_Scale;
    }
}