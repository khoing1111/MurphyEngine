#include "mppch.h"
#include "WindowsWindow.h"

namespace Murphy
{
    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        m_Window = new sf::RenderWindow(sf::VideoMode(props.Width, props.Height), props.Title);
    }

    WindowsWindow::~WindowsWindow()
    {
        delete m_Window;
    }
}