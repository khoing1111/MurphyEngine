#pragma once

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

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
        virtual void Close() const override
        { 
            m_Window->close();
            ImGui::SFML::Shutdown();
        }

        virtual void OnUpdate(sf::Clock& clock) const override
        {
            sf::CircleShape shape(100.f);
            shape.setFillColor(sf::Color::Green);

            sf::Event event;
            while (m_Window->pollEvent(event))
            {
                // Update ImGui Events
                ImGui::SFML::ProcessEvent(event);

                // Translate event to our event system
                if (event.type == sf::Event::Closed)
                    PropagateEvent(IO::WindowClosedEvent());
                else if (event.type == sf::Event::MouseMoved)
                    PropagateEvent(IO::MouseMovedEvent(event.mouseMove.x, event.mouseMove.y));
            }

            ImGui::SFML::Update(*m_Window, clock.restart());

            ImGui::Begin("Hello, world!");
            ImGui::Button("Look at this pretty button");
            ImGui::End();

            m_Window->clear();
            m_Window->draw(shape);
            ImGui::SFML::Render(*m_Window);
            m_Window->display();
        }

    private:
        sf::RenderWindow* m_Window;
    };
}

