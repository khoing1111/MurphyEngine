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
}
