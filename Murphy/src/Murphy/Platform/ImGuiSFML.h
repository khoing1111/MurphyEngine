#pragma once

#include <imgui.h>

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Touch.hpp>
#include <SFML/Window/Window.hpp>

#include <cmath>    // abs
#include <cstddef>  // offsetof, NULL
#include <cstring>  // memcpy

#include "Murphy/Window.h"
#include "Murphy/IO/Event.h"
#include "Murphy/IO/MouseEvents.h"


namespace Murphy::ImGuiSFML
{
    void Init(MP_SPTR<Murphy::Window> window, bool loadDefaultFont = true);
    void OnMouseMove(Murphy::IO::MouseMovedEvent& event);
    void OnMousePressed(Murphy::IO::MousePressedEvent& event);
    void OnMouseReleased(Murphy::IO::MouseReleasedEvent& event);

    void RenderDrawLists(ImDrawData* draw_data);

    //void ProcessEvent(Murphy::IO::Event& event);

    //void Update(sf::RenderWindow& window, sf::Time dt);
    //void Update(sf::Window& window, sf::RenderTarget& target, sf::Time dt);
    //void Update(const sf::Vector2i& mousePos, const sf::Vector2f& displaySize, sf::Time dt);

    //void Render(sf::RenderTarget& target);
    //void Render();

    void Shutdown();

    //void UpdateFontTexture();
    //sf::Texture& GetFontTexture();

    //// joystick functions
    //void SetActiveJoystickId(unsigned int joystickId);
    //void SetJoytickDPadThreshold(float threshold);
    //void SetJoytickLStickThreshold(float threshold);

    //void SetJoystickMapping(int action, unsigned int joystickButton);
    //void SetDPadXAxis(sf::Joystick::Axis dPadXAxis, bool inverted = false);
    //void SetDPadYAxis(sf::Joystick::Axis dPadYAxis, bool inverted = false);
    //void SetLStickXAxis(sf::Joystick::Axis lStickXAxis, bool inverted = false);
    //void SetLStickYAxis(sf::Joystick::Axis lStickYAxis, bool inverted = false);
}