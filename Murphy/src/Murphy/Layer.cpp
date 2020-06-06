#include "mppch.h"
#include "Layer.h"

namespace Murphy
{
    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName)
    {
    }

    Layer::~Layer()
    {
    }

    void Layer::PushEventDispatcher(IO::EventDispatcher* dispatcher)
    {
        m_EventDispatcherStack.PushEventDispatcher(dispatcher);
    }

    void Layer::PopEventDispatcher(IO::EventDispatcher* dispatcher)
    {
        m_EventDispatcherStack.PopEventDispatcher(dispatcher);
    }
}