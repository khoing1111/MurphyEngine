#include "mppch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

namespace Murphy
{

    ImGuiLayer::ImGuiLayer(MP_SPTR<Window> window)
        : Layer("ImGuiLayer"), m_Window(window)
    {
        Murphy::ImGuiSFML::Init(window);

        // Initialize event dispatchers
        PushEventDispatcher(new IO::MouseMovedEventDispatcher(
            std::bind(&ImGuiLayer::OnMouseMoved, this, std::placeholders::_1)
        ));

        PushEventDispatcher(new IO::MousePressedEventDispatcher(
            std::bind(&ImGuiLayer::OnMousePressed, this, std::placeholders::_1)
        ));

        PushEventDispatcher(new IO::MouseReleasedEventDispatcher(
            std::bind(&ImGuiLayer::OnMouseReleased, this, std::placeholders::_1)
        ));
    }

    ImGuiLayer::~ImGuiLayer()
    {
        Murphy::ImGuiSFML::Shutdown();
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        auto window = m_Window.lock();
        io.DisplaySize = { (float)window->GetWidth(), (float)window->GetHeight() };
        io.DeltaTime = m_Clock.getElapsedTime().asSeconds();
        m_Clock.restart();

        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGuiSFML::RenderDrawLists(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnPreRun()
    {
        m_Clock.restart();
    }

    bool ImGuiLayer::OnMouseMoved(IO::MouseMovedEvent & event)
    {
        if (auto window = m_Window.lock(); window && window->HasFocus())
            ImGuiSFML::OnMouseMove(event);

        return true;
    }

    bool ImGuiLayer::OnMousePressed(IO::MousePressedEvent & event)
    {
        if (auto window = m_Window.lock(); window && window->HasFocus())
            ImGuiSFML::OnMousePressed(event);

        return true;
    }

    bool ImGuiLayer::OnMouseReleased(IO::MouseReleasedEvent & event)
    {
        if (auto window = m_Window.lock(); window && window->HasFocus())
            ImGuiSFML::OnMouseReleased(event);

        return true;
    }
}