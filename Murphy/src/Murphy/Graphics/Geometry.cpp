#include "mppch.h"
#include "Geometry.h"


namespace Murphy
{
    //------------------------------------------------------------------
    // STRUCT VECTOR
    void Vector2F::operator=(const Vector2F& source)
    {
        X = source.X;
        Y = source.Y;
    }
}