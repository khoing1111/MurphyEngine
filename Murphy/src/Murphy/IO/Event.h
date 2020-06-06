#pragma once

#include "Murphy/Core.h"

namespace Murphy::IO
{
    enum class EventType
    {
        None = 0,
            
        WindowClosed,           ///< The window requested to be closed (no data)
        WindowResized,          ///< The window was resized (data in event.size)
        WindowLostFocus,        ///< The window lost the focus (no data)
        WindowGainedFocus,      ///< The window gained the focus (no data)
        KeyPressed,             ///< A key was pressed (data in event.key)
        KeyReleased,            ///< A key was released (data in event.key)
        MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
        MouseWheelScrolled,     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
        MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
        MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
        MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
        MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
        MouseLeft,              ///< The mouse cursor left the area of the window (no data)
        JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
        JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
        JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
        JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
        JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)
        TouchBegan,             ///< A touch event began (data in event.touch)
        TouchMoved,             ///< A touch moved (data in event.touch)
        TouchEnded,             ///< A touch event ended (data in event.touch)
        SensorChanged,          ///< A sensor value changed (data in event.sensor)

        Count                   ///< Keep track of number of event type
    };

    enum EventCategory
    {
        None = 0,

        WindowEventCategory         = MP_BIT(0),
        InputEventCategory          = MP_BIT(1),
        KeyboardEventCategory       = MP_BIT(2),
        MouseEventCategory          = MP_BIT(3),
        MouseButtonEventCategory    = MP_BIT(4),
        MouseWheelEvenCategoryt     = MP_BIT(5),
        JoystickEventCategory       = MP_BIT(6),
        TouchEventCategory          = MP_BIT(7),
        SensorEventCategory         = MP_BIT(8),

        Count
    };

    class MURPHY_API Event
    {
    public:
        static EventType GetStaticType() { return EventType::None; }
        virtual EventType GetType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        virtual std::string ToString() const { return GetName(); }
        inline bool InCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        virtual const bool Is(EventType type) { return GetStaticType() == type; }

        bool IsPropagating() { return m_Propagating; }
        void StopPropagating() { m_Propagating = false; }

    private:
        bool m_Propagating = true;
    };

#define MPMC_EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                                virtual EventType GetType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }\
                                virtual const bool Is(EventType compareType) { return GetStaticType() == compareType; }

#define MPMC_EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


    class EventDispatcher
    {
    public:
        virtual bool CheckInboundEvent(IO::Event& event) const = 0;
        virtual bool RunHandler(IO::Event& event) const = 0;

        bool Dispatch(IO::Event& event)
        {
            if (CheckInboundEvent(event))
            {
                if (!RunHandler(event))
                    event.StopPropagating();

                return true;
            }

            return false;
        }
    };

    class AnyEventDispatcher : public EventDispatcher
    {
    private:
        using EventHandler = std::function<bool(Event&)>;
        EventHandler m_Handler;
    public:
        AnyEventDispatcher(EventHandler handler) : m_Handler(handler) {}
        virtual bool CheckInboundEvent(IO::Event& event) const override { return true; }
        virtual bool RunHandler(IO::Event& event) const override { return m_Handler(event); };
    };

#define MPMC_EVENT_DISPATCHER(type) \
    class MURPHY_API type##Dispatcher : public EventDispatcher\
    {\
    private:\
        using EventHandler = std::function<bool(type&)>;\
        EventHandler m_Handler;\
    public:\
        type##Dispatcher(EventHandler handler) : m_Handler(handler) {}\
        virtual bool CheckInboundEvent(IO::Event& event) const override { return event.Is(type::GetStaticType()); }\
        virtual bool RunHandler(IO::Event& event) const override { return m_Handler(*(type*)&event); };\
    }

    class MURPHY_API EventDispatcherStack
    {
    public:
        EventDispatcherStack()
        {
            m_DispatcherInsert = m_Dispatchers.begin();
        }

        ~EventDispatcherStack()
        {
            for (EventDispatcher* dispatcher : m_Dispatchers)
                delete dispatcher;
        }

        void PushEventDispatcher(EventDispatcher* dispatcher) { m_DispatcherInsert = m_Dispatchers.emplace(m_DispatcherInsert, dispatcher); }
        void PopEventDispatcher(EventDispatcher* dispatcher)
        {
            auto it = std::find(m_Dispatchers.begin(), m_Dispatchers.end(), dispatcher);
            if (it != m_Dispatchers.end())
            {
                m_Dispatchers.erase(it);
                m_DispatcherInsert--;
            }

        }

        void PropagateEvent(IO::Event& event) const
        {
            for (auto it = m_Dispatchers.cbegin(); it != m_Dispatchers.cend();)
            {
                if (!event.IsPropagating())
                    break;

                (*it++)->Dispatch(event);
            }
        }

        std::vector<EventDispatcher*>::iterator begin() { return m_Dispatchers.begin(); }
        std::vector<EventDispatcher*>::iterator end() { return m_Dispatchers.end(); }

        std::vector<EventDispatcher*>::const_iterator cbegin() const { return m_Dispatchers.cbegin(); }
        std::vector<EventDispatcher*>::const_iterator cend() const { return m_Dispatchers.cend(); }
    private:
        std::vector<EventDispatcher*> m_Dispatchers;
        std::vector<EventDispatcher*>::iterator m_DispatcherInsert;
    };

    // For debuging only
    inline std::ostream& operator<<(std::ostream& os, const Event& event)
    {
        return os << event.ToString();
    }
}
