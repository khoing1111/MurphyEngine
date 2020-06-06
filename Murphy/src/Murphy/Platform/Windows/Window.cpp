#include "mppch.h"
#include "Window.h"


namespace Murphy
{
    Window* Window::Create(const WindowProps& props)
    {
        return new ::Murphy::Windows::Window(props);
    }
}

namespace Murphy::Windows
{
    Window::Window(const ::Murphy::WindowProps& props)
    {
        m_Window = new sf::RenderWindow(sf::VideoMode(props.Width, props.Height), props.Title);
    }

    Window::~Window()
    {
        delete m_Window;
    }
    
    IO::Mouse::Button Window::SFToIOMouseButton(sf::Mouse::Button button) const
    {
        switch (button)
        {
        case sf::Mouse::Button::Left:
            return IO::Mouse::Button::Left;
        case sf::Mouse::Button::Right:
            return IO::Mouse::Button::Right;
        case sf::Mouse::Button::Middle:
            return IO::Mouse::Button::Middle;
        case sf::Mouse::Button::XButton1:
            return IO::Mouse::Button::XButton1;
        case sf::Mouse::Button::XButton2:
            return IO::Mouse::Button::XButton2;
        default:
            return IO::Mouse::Button::None;
        }
    }
}