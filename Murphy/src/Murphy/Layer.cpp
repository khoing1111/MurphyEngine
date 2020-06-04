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
}