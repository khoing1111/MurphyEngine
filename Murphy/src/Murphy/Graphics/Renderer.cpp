#include "mppch.h"
#include "Renderer.h"

namespace Murphy
{
    void Renderer::Begin(MP_SPTR<Window> window)
    {
        BindWindow(window);
        m_Window->Clear();
    }

    void Renderer::End()
    {
        auto window = ReleaseWindow();
        window->Display();
    }

    void Renderer::BindWindow(MP_SPTR<Window> window)
    {
        MP_COREASSERT(m_Window == nullptr, "Renderer context error. Window already assigned. Did you called End after Begin render?");
        m_Window = window;
    }

    MP_SPTR<Window> Renderer::ReleaseWindow()
    {
        MP_COREASSERT(m_Window != nullptr, "Renderer context error. Window not assigned. Did you called Begin before End render?");
        auto window = m_Window;
        m_Window = nullptr;
        return window;
    }

    MP_SPTR<Window> Renderer::GetWindow()
    {
        MP_COREASSERT(m_Window != nullptr, "Invalid Renderer context. Window not yet assigned. Did you called Begin?");
        return m_Window;
    }
}