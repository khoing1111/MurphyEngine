#include "mppch.h"
#include "Application.h"
#include "IO/WindowEvents.h"

#include <SFML/System/Clock.hpp>
#include "Murphy/Layers/ImGuiLayer.h"


namespace Murphy
{
    Application::Application(Window& window, Renderer& renderer, MP_SPTR<Drawable> rect)
        : m_Window(window), m_Renderer(renderer), m_Rect(rect)
    {
        // Setup Window Event Dispatchers
        auto anyEventDispatcher = new IO::AnyEventDispatcher(
            std::bind(&Application::OnEvent, this, std::placeholders::_1)
        );

        m_Window.PushEventDispatcher(anyEventDispatcher);

        // Setup Layers And Overlays
        //m_LayerStack.PushOverlay(new ImGuiLayer(m_Window));
    }


    Application::~Application()
    {
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
        while (m_IsRunning && m_Window.IsOpen())
        {
            float timeDelta = deltaClock.restart().asSeconds();

            // This will poll events from window and propagate it to dispatcher
            m_Window.Update(timeDelta);

            // Update Layers Logic and render
            for (Layer* layer : m_LayerStack)
            {
                float frameDelta = timeDelta;

                // If time delta is too large, then perform multiple update to catch up.
                // This is currently to lock each update to at least 30fps.
                do {
                    layer->Update(min(0.034, frameDelta));
                    frameDelta -= 0.034;
                } while (frameDelta > 0);
            }

            m_Renderer.ClearFrame(Murphy::Color::White);

            m_Renderer.Draw();
            m_Rect->Draw(&m_Renderer);
            //for (Layer* layer : m_LayerStack)
            //    layer->Render(m_Renderer);

            m_Renderer.EndFrame();
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
