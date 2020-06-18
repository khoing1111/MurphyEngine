#pragma once

#include "Murphy/Layer.h"
#include "Murphy/Window.h"

#include "Murphy/IO/MouseEvents.h"
    /*
namespace Murphy
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer(MP_SPTR<Window>);
        ~ImGuiLayer();

        void Update(float timeDelta);
        virtual void Render(Renderer& renderer) override
        {
            ImGui::Render();
            ImGuiSFML::RenderDrawLists(ImGui::GetDrawData());
        }

    private:
        bool OnMouseMoved(IO::MouseMovedEvent& event);
        bool OnMousePressed(IO::MousePressedEvent& event);
        bool OnMouseReleased(IO::MouseReleasedEvent& event);
        bool OnMouseWheelScrolledEvent(IO::MouseWheelScrolledEvent& event);

        int GetImGuiMouseButton(const IO::Mouse::Button& button) const;

    private:
        MP_WPTR<Window> m_Window;
    };
}
*/
