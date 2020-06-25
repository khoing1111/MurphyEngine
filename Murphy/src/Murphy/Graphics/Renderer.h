#pragma once

#include "Murphy/Core.h"
#include "Murphy/Window.h"
#include "Core.h"

namespace Murphy
{
    class MURPHY_API Renderer
    {
    public:
        Renderer(Window& window);
        virtual ~Renderer() {}

        virtual bool Init() = 0;

        virtual void ClearFrame(const RGBAColor&) = 0;
        virtual bool Draw() = 0;
        virtual void EndFrame() = 0;

    protected:
        Window& m_Window;
    };
}