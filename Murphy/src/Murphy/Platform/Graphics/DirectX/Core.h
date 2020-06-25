#pragma once

#include "Murphy/Graphics/Core.h"

#define MP_COMPTR Microsoft::WRL::ComPtr

namespace Murphy::DirectX
{
    struct Vertex
    {
        Murphy::Vector3F Position;
        Murphy::RGBAColor Color;
    };
}

