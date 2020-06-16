#pragma once

#include "Murphy/Core.h"
#include "Murphy/Graphics/Geometry.h"

namespace Murphy::M2D
{
    class MURPHY_API Transformable
    {
    public:
        Transformable()
            : m_Rotation(0) {}

        virtual ~Transformable() {}

        void SetPosition(float x, float y);
        void SetPosition(Vector2F& position);
        Vector2F GetPosition() const;

        void SetOrigin(float x, float y);
        void SetOrigin(Vector2F& origin);
        Vector2F GetOrigin() const;

        void SetRotation(float rotation);
        float GetRotation() const;

        void SetScale(float x, float y);
        void SetScale(Vector2F& origin);
        Vector2F GetScale() const;

    private:
        Vector2F m_Origin;
        Vector2F m_Position;
        float m_Rotation;
        Vector2F m_Scale;
    };
}

