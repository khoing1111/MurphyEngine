#pragma once

#include "Event.h"

namespace Murphy::IO
{
    namespace Mouse
    {
        enum class Button
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

    class MouseEvent : public Event
    {
    public:
        MouseEvent(int x, int y)
            : m_X(x), m_Y(y) {}

        inline int GetX() const { return m_X; }
        inline int GetY() const { return m_Y; }
    protected:
        int m_X, m_Y;
    };

    class MouseButtonEvent : public MouseEvent
    {
    public:
        MouseButtonEvent(int x, int y, Mouse::Button button)
            : MouseEvent(x, y), m_Button(button) {}

        inline Mouse::Button GetButton() const { return m_Button; }
    protected:
        Mouse::Button m_Button;
    };

    /************************************************************************************************/
    //------------------------------------------------------------------------------------------------
    class MURPHY_API MouseMovedEvent : public MouseEvent
    {
    public:
        MouseMovedEvent(int x, int y)
            : MouseEvent(x, y) {}

        MPMC_EVENT_CLASS_TYPE(MouseMoved)
        MPMC_EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory)
    };

    MPMC_EVENT_DISPATCHER(MouseMovedEvent);

    //------------------------------------------------------------------------------------------------
    class MURPHY_API MousePressedEvent : public MouseButtonEvent
    {
    public:
        MousePressedEvent(int x, int y, Mouse::Button button)
            : MouseButtonEvent(x, y, button) {}

        MPMC_EVENT_CLASS_TYPE(MouseButtonPressed)
        MPMC_EVENT_CLASS_CATEGORY(MouseButtonEventCategory | MouseEventCategory | InputEventCategory)
    };

    MPMC_EVENT_DISPATCHER(MousePressedEvent);

    //------------------------------------------------------------------------------------------------
    class MURPHY_API MouseReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseReleasedEvent(int x, int y, Mouse::Button button)
            : MouseButtonEvent(x, y, button) {}

        MPMC_EVENT_CLASS_TYPE(MouseButtonReleased)
        MPMC_EVENT_CLASS_CATEGORY(MouseButtonEventCategory | MouseEventCategory | InputEventCategory)
    };

    MPMC_EVENT_DISPATCHER(MouseReleasedEvent);

    //------------------------------------------------------------------------------------------------
    class MURPHY_API MouseWheelScrolledEvent : public MouseEvent
    {
    public:
        MouseWheelScrolledEvent(int x, int y, float delta)
            : MouseEvent(x, y), m_Delta(delta) {}

        inline float GetDelta() const { return m_Delta; }

        MPMC_EVENT_CLASS_TYPE(MouseWheelScrolled)
        MPMC_EVENT_CLASS_CATEGORY(MouseWheelEvenCategory | MouseEventCategory | InputEventCategory)
    private:
        float m_Delta;
    };

    MPMC_EVENT_DISPATCHER(MouseWheelScrolledEvent);
}
