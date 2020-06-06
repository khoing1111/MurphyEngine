#pragma once

#include "Murphy/Layer.h"
#include "Murphy/Window.h"
#include "Murphy/Platform/ImGuiSFML.h"

#include "Murphy/IO/MouseEvents.h"
    
namespace Murphy
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer(MP_SPTR<Window>);
        ~ImGuiLayer();

        void OnUpdate();
        void OnPreRun();

    private:
        bool OnMouseMoved(IO::MouseMovedEvent& event);
        bool OnMousePressed(IO::MousePressedEvent& event);
        bool OnMouseReleased(IO::MouseReleasedEvent& event);

    private:
        MP_WPTR<Window> m_Window;
        sf::Clock m_Clock;
    };
}

