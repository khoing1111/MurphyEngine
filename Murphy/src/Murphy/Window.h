#pragma once

#include "Core.h"
#include "IO/Event.h"
#include <functional>

namespace Murphy
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title, unsigned int width, unsigned int height)
            : Title(title), Width(width), Height(height) {}
    };

    class MURPHY_API Window
    {
    public:
        Window() {}
        virtual ~Window() {}

        // Attribute
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual bool IsOpend() const = 0;

        // Action
        virtual void OnUpdate() const = 0;
        virtual void Close() const = 0;

        void PushEventDispatcher(IO::EventDispatcher* dispatcher)
        {
            m_DispatcherStack.PushEventDispatcher(dispatcher);
        }

        void PopEventDispatcher(IO::EventDispatcher* dispatcher)
        {
            m_DispatcherStack.PopEventDispatcher(dispatcher);
        }

        inline void PropagateEvent(IO::Event& event) const
        {
            m_DispatcherStack.PropagateEvent(event);
        }

        static Window* Create(const WindowProps& props);
    private:
        IO::EventDispatcherStack m_DispatcherStack;
    };
}
