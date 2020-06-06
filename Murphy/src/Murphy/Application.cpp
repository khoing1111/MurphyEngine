#include "mppch.h"
#include "Application.h"
#include "IO/WindowEvents.h"

#include <SFML/System/Clock.hpp>
#include "Murphy/Layers/ImGuiLayer.h"


namespace Murphy
{
    Application::Application()
    {
        m_Window = MP_UPTR<Window>(
            Window::Create(WindowProps("MURPHY ENGINE", 1280, 720))
        );

        // Setup Window Event Dispatchers
        auto anyEventDispatcher = new IO::AnyEventDispatcher(
            std::bind(&Application::OnEvent, this, std::placeholders::_1)
        );

        m_Window->PushEventDispatcher(anyEventDispatcher);

        // Setup Layers And Overlays
        m_LayerStack.PushOverlay(new ImGuiLayer(m_Window));
    }

    Application::~Application()
    {
        m_Window->Close();
    }

    bool Application::OnEvent(IO::Event& event)
    {
        if (event.Is(IO::EventType::WindowClosed))
        {
            m_IsRunning = false;
            return false;
        }

        // Loop through Layer in reverse to propagate events
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            if (!event.IsPropagating())
                return false;

            (*--it)->OnEvent(event);
        }

        return true;
    }

    void Application::Run()
    {
        for (Layer* layer : m_LayerStack)
            layer->OnPreRun();

        sf::Clock deltaClock;
        while (m_IsRunning && m_Window->IsOpend())
        {
            // This will poll events from window and propagate it to dispatcher
            m_Window->OnUpdate(deltaClock);

            m_Window->Clear();

            // Update Layers Logic and render
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->Display();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::PopLayer(Layer* layer)
    {
        m_LayerStack.PopLayer(layer);
    }
    
    void Application::PopOverlay(Layer* overlay)
    {
        m_LayerStack.PopOverlay(overlay);
    }
}
