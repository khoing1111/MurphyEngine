#pragma once

#include "Murphy/Core.h"

namespace Murphy
{
    struct MURPHY_API RGBAColor
    {
        UInt8 R, G, B, A;

        RGBAColor();
        RGBAColor(UInt8 r, UInt8 g, UInt8 b, UInt8 a = 255);
        RGBAColor(UInt32 color);

        RGBAColor& operator=(const RGBAColor& source);
        UInt32 ToInt() const;
        std::array<float, 4> ToFloatArray() const;
    };

    struct MURPHY_API RGBColor : public RGBAColor
    {
        const UInt8 A = 255;

        RGBColor();
        RGBColor(UInt8 r, UInt8 g, UInt8 b);
        RGBColor(UInt32 color);
        RGBColor(int color);

        RGBColor& operator=(const RGBColor& source);
    };

    namespace Color
    {
        extern const RGBColor Black;
        extern const RGBColor White;
        extern const RGBColor Red;
        extern const RGBColor Green;
        extern const RGBColor Blue;
    }

    struct MURPHY_API Vector2F
    {
        float X, Y;

        Vector2F();
        Vector2F(float x, float y);

        Vector2F& operator=(const Vector2F& source);
    };

    struct MURPHY_API Vector3F
    {
        float X, Y, Z;
    };

    struct MURPHY_API Matrix4x4
    {
        float elem[4][4];
    };
}
