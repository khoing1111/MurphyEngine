#pragma once

#include "Renderer.h"
#include "Core.h"

namespace Murphy::DirectX
{
    class Bindable
    {
    public:
        virtual ~Bindable() = default;
        virtual void Bind(Renderer&) = 0;
    };
}