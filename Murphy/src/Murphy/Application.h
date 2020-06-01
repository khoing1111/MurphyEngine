#pragma once

#include "Core.h"

namespace Murphy 
{
    class MURPHY_API Application
    {
    public:
        Application();
        virtual ~Application();
        
        void Run();
    };


    // To be define in CLIENT
    Application* CreateApplication();
}

