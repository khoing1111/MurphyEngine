#include "mppch.h"
#include "Geometry.h"

namespace Murphy
{
    //------------------------------------------------------------------
    // STRUCT VECTOR
    Vector2F::Vector2F()
        : X(0.0f), Y(0.0f) {}

    Vector2F::Vector2F(float x, float y)
        : X(x), Y(y) {}

    Vector2F& Vector2F::operator=(const Vector2F& source)
    {
        X = source.X;
        Y = source.Y;
        return *this;
    }
}
