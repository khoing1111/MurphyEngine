#include "mppch.h"

#include <SFML/Window/Event.hpp>

#include "Murphy/Input.h"

namespace Murphy::Input
{
    sf::Mouse::Button ToSFMLMouseButton(IO::Mouse::Button button)
    {
        switch (button)
        {
        case IO::Mouse::Button::Left:
            return sf::Mouse::Left;
        case IO::Mouse::Button::Right:
            return sf::Mouse::Right;
        case IO::Mouse::Button::Middle:
            return sf::Mouse::Middle;
        case IO::Mouse::Button::XButton1:
            return sf::Mouse::XButton1;
        case IO::Mouse::Button::XButton2:
            return sf::Mouse::XButton2;
        default:
            return sf::Mouse::ButtonCount;
        }
    }

    bool IsMousePressed(IO::Mouse::Button& button)
    {
        return sf::Mouse::isButtonPressed(ToSFMLMouseButton(button));
    }
}
