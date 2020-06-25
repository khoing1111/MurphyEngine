#include <Murphy.h>

#include "Murphy/Platform/Graphics/DirectX/Drawables/Rect.h"

MP_UPTR<Murphy::Application> Murphy::CreateApplication(Murphy::Window& window, Murphy::Renderer& renderer)
{
    auto rect = std::make_shared<Murphy::DirectX::Rect>(&renderer);
    return std::make_unique<Murphy::Application>(window, renderer, rect);
}