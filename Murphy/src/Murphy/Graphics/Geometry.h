#pragma once

#include "Murphy/Core.h"
#include "Renderer.h"

namespace Murphy
{
    struct MURPHY_API Vector2F
    {
        float X, Y;

        Vector2F()
            : X(0.0f), Y(0.0f) {}

        Vector2F(float x, float y)
            : X(x), Y(y) {}

        void operator=(const Vector2F& source);
    };

    class MURPHY_API Drawable
    {
    public:
        Drawable() {}
        virtual ~Drawable() {}
        virtual void Draw(Renderer&) const = 0;
    };
}

