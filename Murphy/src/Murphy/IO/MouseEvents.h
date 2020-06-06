#pragma once

#include "Event.h"

namespace Murphy::IO
{
    class MURPHY_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(int x, int y)
            : m_X(x), m_Y(y) {}

        inline int GetX() const { return m_X; }
        inline int GetY() const { return m_Y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMoveEvent: " << m_X << ", " << m_Y;
            return ss.str();
        }

        MPMC_EVENT_CLASS_TYPE(MouseMoved)
        MPMC_EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory)
    private:
        int m_X, m_Y;
    };

    MPMC_EVENT_DISPATCHER(MouseMovedEvent);

    namespace Mouse
    {
        enum Button
        {
            None = 0,

            Left,       ///< The left mouse button
            Right,      ///< The right mouse button
            Middle,     ///< The middle (wheel) mouse button
            XButton1,   ///< The first extra mouse button
            XButton2,   ///< The second extra mouse button

            Count
        };
    }

    class MURPHY_API MousePressedEvent : public Event
    {
    public:
        MousePressedEvent(int x, int y, Mouse::Button button)
            : m_X(x), m_Y(y), m_Button(button) {}

        inline int GetX() const { return m_X; }
        inline int GetY() const { return m_Y; }
        inline Mouse::Button GetButton() const { return m_Button; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MousePressedEvent: " << m_X << ", " << m_Y;
            return ss.str();
        }

        MPMC_EVENT_CLASS_TYPE(MouseButtonPressed)
        MPMC_EVENT_CLASS_CATEGORY(MouseButtonEventCategory | MouseEventCategory | InputEventCategory)
    private:
        int m_X, m_Y;
        Mouse::Button m_Button;
    };

    MPMC_EVENT_DISPATCHER(MousePressedEvent);

    class MURPHY_API MouseReleasedEvent : public Event
    {
    public:
        MouseReleasedEvent(int x, int y, Mouse::Button button)
            : m_X(x), m_Y(y), m_Button(button) {}

        inline int GetX() const { return m_X; }
        inline int GetY() const { return m_Y; }
        inline Mouse::Button GetButton() const { return m_Button; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseReleasedEvent: " << m_X << ", " << m_Y;
            return ss.str();
        }

        MPMC_EVENT_CLASS_TYPE(MouseButtonReleased)
        MPMC_EVENT_CLASS_CATEGORY(MouseButtonEventCategory | MouseEventCategory | InputEventCategory)
    private:
        int m_X, m_Y;
        Mouse::Button m_Button;
    };

    MPMC_EVENT_DISPATCHER(MouseReleasedEvent);
}
