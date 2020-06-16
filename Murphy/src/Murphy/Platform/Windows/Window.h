#pragma once

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Murphy/Window.h"
#include "Murphy/IO/WindowEvents.h"
#include "Murphy/IO/MouseEvents.h"


namespace Murphy::Windows
{
    class Window: public ::Murphy::Window
    {
    public:
        Window(const Murphy::WindowProps& props);
        virtual ~Window();

        virtual unsigned int GetWidth() const override { return m_Window->getSize().x; }
        virtual unsigned int GetHeight() const override { return m_Window->getSize().y; }
        virtual bool IsOpend() const override { return m_Window->isOpen(); }
        virtual bool HasFocus() const override { return m_Window->hasFocus(); }
        virtual void Close() const override
        { 
            m_Window->close();
        }

        virtual void Update(float timeDelta) const override
        {
            sf::Event event;
            while (m_Window->pollEvent(event))
            {
                // Translate event to our event system
                if (event.type == sf::Event::Closed)
                    PropagateEvent(IO::WindowClosedEvent());
                else if (event.type == sf::Event::MouseMoved)
                    PropagateEvent(IO::MouseMovedEvent(event.mouseMove.x, event.mouseMove.y));
                else if (event.type == sf::Event::MouseButtonPressed)
                    PropagateEvent(IO::MousePressedEvent(
                        event.mouseButton.x, event.mouseButton.y, SFToIOMouseButton(event.mouseButton.button)
                    ));
                else if (event.type == sf::Event::MouseButtonReleased)
                    PropagateEvent(IO::MouseReleasedEvent(
                        event.mouseButton.x, event.mouseButton.y, SFToIOMouseButton(event.mouseButton.button)
                    ));
                else if (event.type == sf::Event::MouseWheelScrolled)
                    PropagateEvent(IO::MouseWheelScrolledEvent(
                        event.mouseWheelScroll.x, event.mouseWheelScroll.y, event.mouseWheelScroll.delta
                    ));
            }
        }

        virtual void Clear() const override { m_Window->clear(); }
        virtual void Display() const override { m_Window->display(); }
        virtual void* GetPlatformWindow() const override { return m_Window; };

    private:
        IO::Mouse::Button SFToIOMouseButton(sf::Mouse::Button button) const;

    private:
        sf::RenderWindow* m_Window;
    };
}
