#pragma once

#include "Murphy/Core.h"
#include "Core.h"
#include "Renderer.h"

namespace Murphy
{
    struct MURPHY_API Vector2F
    {
        float X, Y;

        Vector2F();
        Vector2F(float x, float y);

        Vector2F& operator=(const Vector2F& source);
    };

    class MURPHY_API Drawable
    {
    public:
        Drawable() {}
        virtual ~Drawable() {}
        virtual void Draw(Renderer&) const = 0;
    };
}

