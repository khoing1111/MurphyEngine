#pragma once

#include "Murphy/Core.h"
#include "Murphy/Window.h"

namespace Murphy
{
    class MURPHY_API Renderer
    {
    public:
        Renderer()
            : m_Window(nullptr) {}

        virtual ~Renderer() {}

        void Begin(MP_SPTR<Window> window);
        void End();

        MP_SPTR<Window> GetWindow();

    private:
        void BindWindow(MP_SPTR<Window> window);
        MP_SPTR<Window> ReleaseWindow();

    private:
        MP_SPTR<Window> m_Window;
    };
}