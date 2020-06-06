#pragma once

#include "Core.h"
#include "IO/Event.h"

namespace Murphy
{
    class MURPHY_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnPreRun() {}
        virtual void OnEvent(IO::Event& event) 
        {
            m_EventDispatcherStack.PropagateEvent(event);
        }

        inline const std::string& GetName() const { return m_DebugName; }
        void PushEventDispatcher(IO::EventDispatcher* dispatcher);
        void PopEventDispatcher(IO::EventDispatcher* dispatcher);

    private:
        std::string m_DebugName;
        IO::EventDispatcherStack m_EventDispatcherStack;
    };
}
