#pragma once

#include "Event.h"

namespace Murphy::IO
{
    class MURPHY_API WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() {}

        MPMC_EVENT_CLASS_TYPE(WindowClosed)
        MPMC_EVENT_CLASS_CATEGORY(WindowEventCategory)
    };

    MPMC_EVENT_DISPATCHER(WindowClosedEvent);

}
