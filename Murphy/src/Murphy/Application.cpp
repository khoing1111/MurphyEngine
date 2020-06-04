#include "mppch.h"
#include "Application.h"
#include "IO/WindowEvents.h"


namespace Murphy
{
#define BIND_EVENT_HANDLER(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = MP_UPTR<Window>(
            Window::Create(WindowProps("MURPHY ENGINE", 1280, 720))
        );

        auto anyEventHandler = BIND_EVENT_HANDLER(Application::OnEvent);
        auto anyEventDispatcher = new IO::AnyEventDispatcher(anyEventHandler);
        m_Window->PushEventDispatcher(anyEventDispatcher);

    }

    Application::~Application()
    {
    }

    bool Application::OnEvent(IO::Event& event)
    {
        if (event.Is(IO::EventType::WindowClosed))
        {
            m_Window->Close();
            return false;
        }

        // Loop through Layer in reverse to propagate events
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            if (!event.IsPropagating())
                break;

            (*--it)->OnEvent(event);
        }
    }

    void Application::Run()
    {
        while (m_Window->IsOpend())
        {
            // This will poll events from window and propagate it to dispatcher
            m_Window->OnUpdate();

            // Update Layers Logic
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();
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
