#include "mppch.h"
#include "Core.h"

namespace Murphy
{
    RGBAColor::RGBAColor(UInt8 r, UInt8 g, UInt8 b, UInt8 a)
        : R(r), G(g), B(b), A(a) {}

    RGBAColor::RGBAColor()
        : R(0), G(0), B(0), A(255) {}

    RGBAColor::RGBAColor(UInt32 color)
    {
        R = color >> 24;
        G = color >> 16;
        B = color >> 8;
        A = color;
    }

    UInt32 RGBAColor::ToInt() const
    {
        return (UInt32)R << 24 | (UInt32)G << 16 | (UInt32)B << 8 | (UInt32)A;
    }

    std::array<float, 4> RGBAColor::ToFloatArray() const
    {
        return { (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255, };
    }

    RGBAColor& RGBAColor::operator=(const RGBAColor& source)
    {
        R = source.R;
        G = source.G;
        B = source.B;
        A = source.A;
        return *this;
    }

    RGBColor::RGBColor(UInt8 r, UInt8 g, UInt8 b)
        : RGBAColor(r, g, b, 255) {}

    RGBColor::RGBColor()
        : RGBAColor() {}

    RGBColor::RGBColor(UInt32 color)
    {
        R = color >> 16;
        G = color >> 8;
        B = color >> 0;
    }

    RGBColor::RGBColor(int color)
        : RGBColor((UInt32)color) {}

    RGBColor& RGBColor::operator=(const RGBColor& source)
    {
        R = source.R;
        G = source.G;
        B = source.B;
        return *this;
    }

    namespace Color
    {
        extern const RGBColor Black(0x000000);
        extern const RGBColor White(0xFFFFFF);
        extern const RGBColor Red(0xFF0000);
        extern const RGBColor Green(0x00FF00);
        extern const RGBColor Blue(0x0000FF);
    }
}
