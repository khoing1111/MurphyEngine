#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h" 
#include "Window.h"
#include "IO/Event.h"
#include "IO/WindowEvents.h"
#include "Graphics/Renderer.h"

namespace Murphy 
{
    class MURPHY_API Application
    {
    public:
        Application(Window& window, Renderer& renderer);
        virtual ~Application();
        
        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        bool OnEvent(IO::Event& event);

    private:
        LayerStack m_LayerStack;
        Window& m_Window;
        Renderer& m_Renderer;
        bool m_IsRunning = true;
    };

    // To be define in CLIENT
    MP_UPTR<Application> CreateApplication(Window&, Renderer&);
}

