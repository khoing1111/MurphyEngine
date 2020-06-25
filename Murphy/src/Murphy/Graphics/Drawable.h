#pragma once

#include "Renderer.h"

namespace Murphy
{
    class MURPHY_API Drawable
    {
    public:
        Drawable() {}
        virtual ~Drawable() = default;
        virtual void Draw(Renderer* renderer) = 0;
    };
}
