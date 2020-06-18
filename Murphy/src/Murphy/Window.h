#pragma once

#include "Core.h"
#include "IO/Event.h"
#include <functional>

#include <SFML/System/Clock.hpp>

namespace Murphy
{
    enum DisplayStyle
    {
        None = 0,                           ///< No border / title bar (this flag and all others are mutually exclusive)
        Titlebar = 1 << 0,                  ///< Title bar + fixed border
        Resize = 1 << 1,                    ///< Title bar + resizable border + maximize button
        Close = 1 << 2,                     ///< Title bar + close button
        Fullscreen = 1 << 3,                ///< Fullscreen mode (this flag and all others are mutually exclusive)

        Default = Titlebar | Resize | Close ///< Default window style
    };

    struct WindowProps
    {
        std::wstring Title;
        unsigned int Width;
        unsigned int Height;
        UInt32 Style;

        WindowProps(std::wstring title, unsigned int width, unsigned int height, UInt32 style=DisplayStyle::Default)
            : Title(title), Width(width), Height(height), Style(style) {}
    };

    class MURPHY_API Window
    {
    public:
        Window() {}
        virtual ~Window() {}

        // Attribute
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual bool IsOpen() const = 0;
        virtual bool HasFocus() const = 0;

        // Action
        virtual void Update(float timeDelta) const = 0;
        virtual void Clear() const = 0;
        virtual void Display() const = 0;
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
    public:
        IO::EventDispatcherStack m_DispatcherStack;
    };
}
