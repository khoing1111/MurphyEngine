#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h" 
#include "Window.h"
#include "IO/Event.h"
#include "IO/WindowEvents.h"

namespace Murphy 
{
    class MURPHY_API Application
    {
    public:
        Application();
        virtual ~Application();
        
        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        bool OnEvent(IO::Event& event);

    private:
        LayerStack m_LayerStack;
        MP_UPTR<Window> m_Window;
    };


    // To be define in CLIENT
    Application* CreateApplication();
}

