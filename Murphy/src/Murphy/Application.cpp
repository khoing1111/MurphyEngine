#include "Application.h"

#include <SFML/Graphics.hpp>

namespace Murphy
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
        sf::Event event;
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
    }
}