#pragma once

#include <SFML/Graphics.hpp>
#include "Murphy/Window.h"
#include "Murphy/IO/WindowEvents.h"
#include "Murphy/IO/MouseEvents.h"

namespace Murphy
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const Murphy::WindowProps& props);
        virtual ~WindowsWindow();

        virtual unsigned int GetWidth() const override { return m_Window->getSize().x; }
        virtual unsigned int GetHeight() const override { return m_Window->getSize().y; }
        virtual bool IsOpend() const override { return m_Window->isOpen(); }
        virtual void Close() const override { m_Window->close(); }

        virtual void OnUpdate() const override
        {
            sf::Event event;
            while (m_Window->pollEvent(event))
            {
                // Translate event to our event system
                if (event.type == sf::Event::Closed)
                    PropagateEvent(IO::WindowClosedEvent());
                else if (event.type == sf::Event::MouseMoved)
                    PropagateEvent(IO::MouseMovedEvent(event.mouseMove.x, event.mouseMove.y));
            }
        }

    private:
        sf::RenderWindow* m_Window;
    };
}

